#!/bin/sh
cat <<EOF
static const char *keytable[] =
{
EOF
sed -n -r -e '/^#define (KEY|BTN)_/ s/#define ([A-Z0-9_]+)[ \t]*((0x)?[0-9a-f]+)$/  [\2] = "\1",/p'
cat <<EOF
};

/* vim:set ts=2 sw=2 et: */
EOF
