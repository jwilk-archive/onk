#!/bin/sh
export LC_ALL=POSIX
cat <<EOF
typedef struct { char *name; int value; } keylist_item_t;
static const keylist_item_t keylist[] =
{
EOF
sed -n -r -e '/^#define (KEY|BTN)_/ s/#define ([A-Z0-9_]+)[ \t]*((0x)?[0-9a-f]+)$/ { .name = "\1", .value = \2 },/p' | sort
cat <<EOF
};

/* vim:set ts=2 sw=2 et: */
EOF
