all: keysniff onk

test: all
	./onk < onk.conf

clean:
	rm -f keysniff onk a.out

keysniff: keysniff.c
	gcc -Wall -s -Os ${<} -o ${@}

onk: onk.c
	gcc -Wall -s -Os ${<} -o ${@}

.PHONY: all test clean

# vim: ts=4
