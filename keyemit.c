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

#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <linux/input.h>
#include "keylist.h"

static int compare_keylist_item(const void *a, const void *b)
{
  return strcmp(((keylist_item_t*)a)->name, ((keylist_item_t*)b)->name);
}

static inline void send_event(FILE *file, uint16_t type, uint16_t code, int32_t value)
{
  struct input_event ev;
  gettimeofday(&ev.time, NULL);
  ev.type = type;
  ev.code = code;
  ev.value = value;
  if (fwrite(&ev, sizeof(struct input_event), 1, file) != 1)
  {
    perror(NULL);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char **argv)
{
  char *fname = "/dev/input/event0";
  if (argc > 1)
    fname = argv[1];

  FILE *file = fopen(fname, "w");
  if (!file)
  {
    perror(fname);
    return EXIT_FAILURE;
  }

  char *str = NULL;
  ssize_t strlen;
  size_t buflen = 0;

  while ((strlen = getline(&str, &buflen, stdin)) != -1)
  {
    int key;
    if (strlen > 0 && str[strlen - 1] == '\n')
      str[strlen - 1] = '\0';
    if (sscanf(str, "%d", &key) != 1)
    {
      keylist_item_t goal = { .name = str };
      keylist_item_t *result =
        bsearch(&goal, keylist, sizeof keylist / sizeof (keylist_item_t), sizeof (keylist_item_t), compare_keylist_item);
      if (result == NULL)
        continue;
      key = result->value;
    }
    if (key < 0 || key > KEY_MAX)
      continue;
    send_event(file, EV_KEY, key, 1);
    send_event(file, EV_SYN, SYN_REPORT, 0);
    send_event(file, EV_KEY, key, 0);
    send_event(file, EV_SYN, SYN_REPORT, 0);
    fflush(file);
  }
  fclose(file);
  return EXIT_SUCCESS;
}

/* vim:set ts=2 sts=2 sw=2 et: */
