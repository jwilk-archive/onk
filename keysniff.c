/* 2, 7 Jan 2004 */

#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>

struct input_event ev;

int main(int argc, char** argv)
{
  char* fname = "/dev/input/event0";
  FILE* file;
  
  if (argc > 1)
    fname = argv[1];

  file = fopen(fname, "r");
  if (!file)
    return EXIT_FAILURE;

  while (fread(&ev, sizeof(ev), 1, file) > 0)
  {
    if (ev.value)
      fprintf(stderr, "%d ", ev.code);
  }

  return EXIT_SUCCESS;
}

/* vim:set ts=2 sw=2 et: */
