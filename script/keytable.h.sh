#!/bin/sh

# Copyright © 2005, 2006, 2007, 2008 Jakub Wilk <jwilk@jwilk.net>.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 dated June, 1991.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.

cat <<EOF
static const char *keytable[] =
{
EOF
sed -n -r -e '/^#define (KEY|BTN)_/ s/#define ([A-Z0-9_]+)[ \t]*((0x)?[0-9a-f]+)$/  [\2] = "\1",/p'
cat <<EOF
};

/* vim:set ts=2 sw=2 et: */
EOF
