#!/bin/sh
export LC_ALL=POSIX
echo 'typedef struct { char *name; int value; } keylist_item_t;'
echo 'static const keylist_item_t keylist[] ='
echo '{'
sed -n -re '/^#define (KEY|BTN)_/ s/#define ([A-Z0-9_]+)[ \t]*((0x)?[0-9a-f]+)$/ { .name = "\1", .value = \2 },/p' | sort
echo '};'
echo
echo '/* vim:set ts=2 sw=2 et: */'

# vim:ts=4
