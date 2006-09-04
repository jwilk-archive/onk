CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -W -Os
CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)
EXEFILES = keyemit keysniff onk

.PHONY: all
all: $(EXEFILES)

.PHONY: clean
clean:
	$(RM) $(EXEFILES) *.o *.h

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
