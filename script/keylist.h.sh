#!/bin/sh

# Copyright © 2005-2008 Jakub Wilk <jwilk@jwilk.net>.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 dated June, 1991.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.

export LC_ALL=POSIX
cat <<EOF
typedef struct { char *name; int value; } keylist_item_t;
static const keylist_item_t keylist[] =
{
EOF
sed -n -r -e '/^#define (KEY|BTN)_/ s/#define ([A-Z0-9_]+)[ \t]*((0x)?[0-9a-f]+)$/ { .name = "\1", .value = \2 },/p' | sort
cat <<EOF
};

/* vim:set ts=2 sts=2 sw=2 et: */
EOF
