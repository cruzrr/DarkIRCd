package DarkIRCd::Proto::RFC1459;

# This module defines the protocol that is described
# in RFC1459 (see doc/rfc1459.txt)
#
# Copyright (C) 2012 cruzrr
# Website: http://www.cruzrr.com

use strict;
use warnings;

sub new {
	my $class = shift;
	my $self = { };

	return bless($self, $class);
}

sub def {
	my $class = shift;
	my $proto = (
		WELCOME		=> '001',
		SERV_HOST	=> '002',
		SERV_CRET	=> '003',
		SERV_LINF	=> '004',
		SERV_INFO	=> '005',
		
		AWAY		=> '301',
		UNAWAY		=> '305',
		NOWAWAY		=> '306',
		WHOIS_USER	=> '311',
		WHOIS_SERV	=> '312',
		
	);

	return $proto;
}

1;
