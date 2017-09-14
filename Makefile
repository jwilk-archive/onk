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

CC ?= gcc
CFLAGS ?= -g -O2
CFLAGS += -std=gnu99 -Wall -Wextra
CFLAGS += -Wno-override-init -Wno-initializer-overrides

PREFIX = /usr/local
bindir = $(PREFIX)/bin
mandir = $(PREFIX)/share/man

cfiles = $(wildcard *.c)
ofiles = $(cfiles:.c=.o)
exefiles = keyemit keysniff onk

input.h = $(or $(wildcard /usr/include/linux/input-event-codes.h) /usr/include/linux/input.h)

.PHONY: all
all: $(exefiles)

.PHONY: install
install: $(exefiles)
	install -d $(DESTDIR)$(bindir)
	echo $(exefiles) \
	| xargs -n1 \
	| xargs -t -I{} install -m 644 {} $(DESTDIR)$(bindir)
ifeq "$(wildcard .git doc/*.8)" ".git"
	# run "$(MAKE) -C doc" to build the manpages
else
	install -d $(DESTDIR)$(mandir)/man8
	echo $(notdir $(wildcard doc/*.8)) \
	| xargs -n1 \
	| xargs -t -I{} install -m 644 doc/{} $(DESTDIR)$(mandir)/man8
endif

.PHONY: clean
clean:
	rm -f $(exefiles) *.o *.h

keylist.h: $(input.h) tools/keylist.h.sh
	tools/keylist.h.sh < $(<) > $(@)

keytable.h: $(input.h) tools/keytable.h.sh
	tools/keytable.h.sh < $(<) > $(@)

$(exefiles): %: %.o
	$(LINK.c) $(^) $(LDLIBS) -o $(@)

include Makefile.dep

# vim:ts=4 sts=4 sw=4 noet
