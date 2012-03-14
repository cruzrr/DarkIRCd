package DarkIRCd::Sockets::IPv4;

# This module provides an interface to deal with clients who are using
# IPv6.
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
	my ($class) = @_;
	my $self    = { };
	
	return bless($self, $class);
}

1;
