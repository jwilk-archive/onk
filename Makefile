CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Os
CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
EXEFILES = keyemit keysniff onk

all: $(EXEFILES)

test: all
	./onk < onk.conf

clean:
	rm -f $(EXEFILES) *.o *.h

keylist.h: /usr/include/linux/input.h
	./script/keylist.h.sh < ${<} > ${@}

keytable.h: /usr/include/linux/input.h
	./script/keytable.h.sh < ${<} > ${@}

$(EXEFILES): %: %.o
	$(CC) $(CFLAGS) -s ${<} -o ${@}

$(OFILES): %.o: %.c
	$(CC) $(CFLAGS) -c ${<} -o ${@}

.PHONY: all test clean

include Makefile.dep

# vim: ts=4
