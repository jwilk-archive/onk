/**
 * Copyright © 2005-2008 Jakub Wilk <jwilk@jwilk.net>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 dated June, 1991.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include "keytable.h"

int main(int argc, char **argv)
{
  char *fname = "/dev/input/event0";
  if (argc > 1)
    fname = argv[1];

  FILE *file = fopen(fname, "r");
  if (!file)
  {
    perror(fname);
    return EXIT_FAILURE;
  }

  struct input_event ev;
  while (fread(&ev, sizeof(ev), 1, file) > 0)
  {
    if (!ev.value || ev.type != EV_KEY || ev.code > KEY_MAX)
      continue;
    if (keytable[ev.code] != NULL)
      fprintf(stderr, "%s ", keytable[ev.code]);
    fprintf(stderr, "%d\n", ev.code);
  }
  fclose(file);
  return EXIT_SUCCESS;
}

/* vim:set ts=2 sts=2 sw=2 et: */
