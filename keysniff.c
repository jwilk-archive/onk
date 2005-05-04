/* 2, 7 Jan 2005; 1 May 2005 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include "keytable.h"


int main(int argc, char** argv)
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

/* vim:set ts=2 sw=2 et: */
