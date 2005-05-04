/* 7 Jan 2005; 1 May 2005 */

#define _GNU_SOURCE
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/input.h>

#include "keylist.h"

static inline char freadch(FILE *file)
{
  char buf = '\0';
  fread((void*)&buf, sizeof(char), 1, file);
  return buf;
}

int compare_keylist_item(const void *a, const void *b)
{
  return strcmp(((keylist_item_t*)a)->name, ((keylist_item_t*)b)->name);
}

int main(void)
{
  char *tmp, *str, *triggers[KEY_MAX + 1];
  char *fname = NULL;
  size_t junk;

  memset(triggers, 0, sizeof(triggers));
  if (getline(&fname, &junk, stdin) == -1)
  {
    perror(NULL);
    return EXIT_FAILURE;
  }
  tmp = strchr(fname, '\n');
  if (tmp != NULL)
    *tmp = '\0';
  while (true)
  {
    int key;
    int key2 = -1;
    str = NULL;
    if (getdelim(&str, &junk, '\t', stdin) == -1)
      break;
    if (sscanf(str, "%d..%d", &key, &key2) < 1)
    {
      tmp = strchr(str, '\t');
      if (tmp != NULL)
        *tmp = '\0';
      keylist_item_t goal = { .name = str };
      keylist_item_t *result =
        bsearch(&goal, keylist, sizeof(keylist)/sizeof(keylist_item_t), sizeof(keylist_item_t), compare_keylist_item); 
      if (result == NULL)
        return EXIT_FAILURE;
      key = result->value;
    } 
    if (key < 0 || key > KEY_MAX || key2 > KEY_MAX)
      return EXIT_FAILURE;
    str = NULL;
    if (getline(&str, &junk, stdin) == -1)
    {
      perror(NULL);
      return EXIT_FAILURE;
    }
    do
      triggers[key++] = str;
    while (key2 > 0 && key <= key2);
  }

  struct input_event ev;
  FILE* file = fopen(fname, "r");
  if (file == NULL) 
  { 
    perror(fname); 
    return EXIT_FAILURE; 
  }

  if (daemon(0, 0) == -1 || nice(NZERO/2) == -1) 
  { 
    perror(NULL); 
    return EXIT_FAILURE; 
  }
  while (fread(&ev, sizeof(ev), 1, file) > 0)
  {
    if (!ev.value || ev.type != EV_KEY || ev.code > KEY_MAX)
      continue;
    if (triggers[ev.code])
      system(triggers[ev.code]) == -1;
  }
  fclose(file);
  return EXIT_SUCCESS;
}

/* vim:set ts=2 sw=2 et: */
