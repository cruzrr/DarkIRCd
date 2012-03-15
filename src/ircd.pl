#!/usr/bin/perl

# DarkIRCd - Modular and Lightweight IRCd in Perl.
#
# Copyright (C) 2012 cruzrr
# Website: http://www.cruzrr.com

use strict;
use warnings;
use lib '../lib';
use DarkIRCd::Core;

my $ircd = DarkIRCd::Core->new('../conf/DarkIRCd.conf');

$ircd->start(); # this will NEVER return.
