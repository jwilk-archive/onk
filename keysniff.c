/**
 * Copyright © 2005-2016 Jakub Wilk <jwilk@jwilk.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
    if (ev.code < KEY_MAX &&ev.code < KEY_MAX &&  keytable[ev.code] != NULL)
      fprintf(stderr, "%s ", keytable[ev.code]);
    fprintf(stderr, "%d\n", ev.code);
  }
  fclose(file);
  return EXIT_SUCCESS;
}

/* vim:set ts=2 sts=2 sw=2 et: */
