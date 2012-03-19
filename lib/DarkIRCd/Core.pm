package DarkIRCd::Core;

# This is the Core module of DarkIRCd.
#
#
# Copyright (C) 2012 cruzrr
# Website: http://www.cruzrr.com
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

use strict;
use warnings;
use DarkIRCd::Config;

our ($sel, $config, %outbuffer, %inbuffer, $starttime, @pings, $checktime, $lastout);

sub new {
    my ($class, $configFile) = @_;
    my $config_parser        = DarkIRCd::Config->new($configFile);
    my $self                 = { };
    $sel                     = IO::Select->new();
    $config                  = $config_parser-parse();
    
    my @ports = split(',', $config->{Server}->{ports});
    
    foreach my $portlist (@ports) {
        my ($port, $flags) = split(/\:/, $portlist);
        my @flaglist = split(/\+/, $flags);
        my ($useSSL, $useIPV6, $useIPV4);
        
        for (my $i = 0; $i < $#flaglist; $i++) {
            if ($flaglist[$i] eq "SSL") {
                $useSSL = 1;
            } elsif ($flaglist[$i] eq "IPV4") {
                $useIPV4 = 1;
            } elsif ($flaglist[$i] eq "IPV6") {
                $useIPV6 = 1;
            }
       }
       
       my $s4 = DarkIRCd::Sockets::IPv4->new();
       my $s6 = DarkIRCd::Sockets::IPv6->new();
       my $t;
       
       # create the socket
       if ($useIPV4) {
           $t = $s4->createServer($config->{Server}->{bindaddr}, $port);
           $sel->add($t);
       } elsif ($useIPV6) {
           $t = $s6->createServer($config->{Server}->{bindaddr6}, $port);
           $sel->add($t);
       } elsif ($useIPV4 && $useSSL) {
           $t = $s4->createServer($config->{Server}->{bindaddr}, $port, 1, $config->{Server}->{SSLCert}, $config->{Server}->{SSLKey});
           $sel->add($t);
       } elsif ($useIPV4 && $useSSL) {
           $t = $s6->createServer($config->{Server}->{bindaddr6}, $port, 1, $config->{Server}->{SSLCert}, $config->{Server}->{SSLKey});
           $sel->add($t);
      }
    }
    
    return bless($self, $class);
}


sub start {
    $starttime      = time;
    $checktime      = time;
    $lastout        = 0;
    main_loop();
}


# this was taken from an IRC bot I wrote a year or so back
# it might be easier to just write a new mainloop than try
# to port this one... -ablakely

sub main_loop() {
    while(1) {
        foreach my $fh ($sel->can_read(1)) {
            my ($tmp, $char);
            $tmp = sysread($fh, $char, 1024);
            close $fh unless defined $tmp and length $char;
            $inbuffer{$fh} .= $char;
                        
            while (my ($theline, $therest) = $inbuffer{$fh} =~ /([^\n]*)\n(.*)/s) {
                $inbuffer{$fh} .= $therest;
                $theline =~ s/\r$//;
                server_in($theline, $fh);
            }
        }
        
        my $count = 0;
        my $time  = time;
            
        for my $num (0 .. 3) {
            last if ($lastout >= $time);
            while($_ = shift(@{$queue[$num]})) {
                if (length($_) > 512) {
                    $_ = substr($_, 0, 511);
                }
            }
                
            fh_distribute($_);
                
            if (length($_) > 400) {
                $lastout = $time + 5;
                $count++;
                last;
            }
            $count++;
               
            if ($lastout < $time - 20) {
                $lastout = $time - 20;
                last;
            }
            elsif ($lastout < $time - 15) {
                $lastout = $time - 15;
                next;
            }
            elsif ($lastout < $time - 10) {
                $lastout = $time - 10;
                next;
            } else {
                $lastout = $time + 1;
            }
    		last if $count >= 1;
        }
    	last if $count >= 1;
    }
    
    foreach my $fh ($sel->can_write(0)) {
        flush_out($fh);
    }
    		
    if ($starttime + 60 < $time && $checktime + 30 < $time) {
        $checktime = $time;
        process_pongs();
    }
    		
    for (@timeout) {
        if (defined($_->{'time'}) && $time >= $_->{'time'}) {
            delete($_->{'time'});
            my ($module, $sub) = ($_->{module}, $_->{'sub'});
            eval("${$module}::$sub();");
        }
    }
}

1;
