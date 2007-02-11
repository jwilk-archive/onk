DOCBOOK_XSL = /usr/share/xml/docbook/stylesheet/nwalsh/manpages/docbook.xsl
VERSION=$(shell sed -n -e '/onk ([0-9]*[^0-9]*\([0-9.-]*\)).*/ { s//\1/; p; q; } ' < debian/changelog)
CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -W -Os
CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
EXEFILES = keyemit keysniff onk

.PHONY: all
all: $(EXEFILES)

.PHONY: clean
clean:
	$(RM) $(EXEFILES) *.o *.h doc/*.[0-9]

.PHONY: doc
doc: doc/keysniff.1

%.1: %.xml
	sed -e "s/\(<!ENTITY version '\).*\('>\)/\1$(VERSION)\2/" < $(<) | xsltproc --path doc/ --xinclude --output $(@) $(DOCBOOK_XSL) -

keylist.h: /usr/include/linux/input.h
	./script/keylist.h.sh < ${<} > ${@}

keytable.h: /usr/include/linux/input.h
	./script/keytable.h.sh < ${<} > ${@}

$(EXEFILES): %: %.o
	$(CC) $(CFLAGS) -s ${<} -o ${@}

$(OFILES): %.o: %.c
	$(CC) $(CFLAGS) -c ${<} -o ${@}

include Makefile.dep

# vim: ts=4
