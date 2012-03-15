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

our ($sel, $config, %outbuffer, %inbuffer);

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
    

1;
