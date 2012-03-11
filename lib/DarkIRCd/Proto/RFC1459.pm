package DarkIRCd::Proto::RFC1459;

# This module defines the protocol that is described
# in RFC1459 (see doc/rfc1459.txt)
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

sub new {
	my $class = shift;
	my $self = { };

	return bless($self, $class);
}

sub proto_def {
	my $class = shift;
	my $proto = (
		WELCOME     => '001',
		SERV_HOST   => '002',
		SERV_CRET   => '003',
		SERV_LINF   => '004',
		SERV_INFO   => '005',
		
		AWAY        => '301',
		UNAWAY      => '305',
		NOWAWAY     => '306',
		WHOIS_USER  => '311',
		WHOIS_SERV  => '312',
		WHOIS_OPER  => '313',
		WHOWAS_USR  => '314',
		WHOIS_IDLE  => '317',
		WHOIS_END   => '318',
		WHOIS_CHAN  => '319',
		
		TOPIC       => '332',
		NOTOPIC     => '331',
		INVITING    => '341',
		NAME_REPLY  => '353',
		NAME_END    => '366',
		WHOWAS_END  => '369',
		
		LIST_START  => '321',
		LIST        => '322',
		LIST_END    => '323',
		
		VERSION     => '351',
		MOTD_START  => '375',
		MOTD        => '372',
		MOTD_END    => '376',
		WHO         => '352',
		WHO_END     => '315',
		
		CHAN_MODES  => '324',
		BAN_LIST    => '367',
		BAN_END     => '368',
		
		USER_ISOP   => '381',
		TIME        => '391'
	);

	return $proto;
}

sub error_def {
	my $class = shift;
	my $errors = (
		NOSUCHNICK  => '401',
		NOSUCHSERV  => '402',
		CANNOTSEND  => '404',
		WASNONICK   => '406',
		NORECIPIENT => '411',
		NOTEXTTOSND => '412',
		NOGIVENNICK => '431',
		BADNICK     => '432',
		NAMEINUSE   => '433',
		USRNOTTHERE => '441',
		USERONCHAN  => '443',
		NOSUCHCHAN  => '403',
		NOTONCHAN   => '442',
		NEEDMOREPRM => '461',
		WRONGPASS   => '464',
		YOUAREBANND => '465',
		KEYSET      => '467',
		CHANISFULL  => '471',
		INVITEONLY  => '473',
		BANNED      => '474',
		BADCHANKEY  => '475',
		NOPRIVS     => '481',
		CHANOPSREQ  => '482',
		NOOPERHOST  => '491',
		UNLIKEUSER  => '502'
	);

	return $errors;
}

sub checknick {
	my ($class, $nick) = @_;
	
	if ($nick =~ /^[^a-z]|[^\W_^`\\\[\]{}]/i) {
		return 0;
	} else {
		return 1;
	}
}

sub checkchan {
	my ($class, $chan) = @_;
	
	if ($chan =~ /[\x00\x07\n\r ,]/) {
		return 0;
	} else {
		return 1;
	}
}

sub checkchankey {
	my ($class, $key) = @_;
	
	if ($key =~ /[\x80-\uFFFF\x00\t\n\x0B\x0C\r ,]/) {
		return 0;
	} else {
		return 1;
	}
}

1;
