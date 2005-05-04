#!/bin/sh
echo 'static const char *keytable[] ='
echo '{'
sed -n -re '/^#define (KEY|BTN)_/ s/#define ([A-Z0-9_]+)[ \t]*((0x)?[0-9a-f]+)$/  [\2] = "\1",/p'
echo '};'
echo
echo '/* vim:set ts=2 sw=2 et: */'

# vim:ts=4
