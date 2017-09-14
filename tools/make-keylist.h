#!/bin/sh

# Copyright © 2005-2017 Jakub Wilk <jwilk@jwilk.net>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the “Software”), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

export LC_ALL=POSIX
cat <<EOF
typedef struct { char *name; int value; } keylist_item_t;
static const keylist_item_t keylist[] =
{
EOF
perl -n -e 's/^#define\s+((?:KEY|BTN)_\w+)\s+((?:[0-9]+|0[xX])[0-9a-fA-F]+)\s*$/    { .name = "\1", .value = \2 },\n/ and print' | sort
cat <<EOF
};

/* vim:set ts=4 sts=4 sw=4 et: */
EOF

# vim:ft=sh
