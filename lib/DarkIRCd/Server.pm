package DarkIRCd::Server;

use v5.10;
use Carp;
use strict;
use warnings;
use IO::Socket;
use IO::Select;

our ($server, $sockets);

sub new {
	my $class  = shift;
	my $self   = {};
	my ($port) = @_;

	$server = new IO::Socket::INET(
		"Listen"	=> 1,
		"LocalPort"	=> $port,
		"Blocking"	=> 0)
	or return undef;

	$sockets = new IO::Select($server) or return undef;
	return bless($self, $class);
}

1;
