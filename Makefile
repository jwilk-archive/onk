CC = gcc
CFLAGS = -g -O2
CFLAGS += -std=gnu99 -Wall -Wextra -Wno-initializer-overrides

cfiles = $(wildcard *.c)
ofiles = $(cfiles:.c=.o)
exefiles = keyemit keysniff onk

version = $(shell head -n1 doc/changelog | cut -d ' ' -f2 | tr -d '()')

input.h = $(or $(wildcard /usr/include/linux/input-event-codes.h) /usr/include/linux/input.h)

docbook_xsl = http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl
xsltproc_opts = --param man.authors.section.enabled 0

.PHONY: all
all: $(exefiles)

.PHONY: clean
clean:
	rm -f $(exefiles) *.o *.h doc/*.[0-9]

.PHONY: doc
doc: doc/keysniff.8 doc/keyemit.8 doc/onk.8

%.8: %.xml
	sed -e "s/\(<!ENTITY version '\).*\('>\)/\1$(version)\2/" < $(<) \
	| xsltproc $(xsltproc_opts) --path doc/ --xinclude --output $(@) $(docbook_xsl) -

keylist.h: $(input.h)
	./script/keylist.h.sh < $(<) > $(@)

keytable.h: $(input.h)
	./script/keytable.h.sh < $(<) > $(@)

$(exefiles): %: %.o
	$(LINK.c) $(<) -o $(@)

include Makefile.dep

# vim:ts=4 sts=4 sw=4 noet
