/* 7 Jan 2004 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/input.h>

#define max_trigger_no 0x7ff

static inline char freadch(FILE *file)
{
  char buf='\0';
  fread((void*)&buf, sizeof(char), 1, file);
  return buf;
}

int main()
{
  char* triggers[max_trigger_no+1];
  char fname[] = "/dev/input/event$";
  char ch;

  memset(triggers, 0, sizeof(triggers));
  
#define fetch do { ch = freadch(stdin); } while(0)
#define fail do { return EXIT_FAILURE; } while(0)
#define digit (ch >= '0' && ch<='9')
#define white (ch <= ' ' && ch != '\0')  
#define nwhite (ch > ' ')  
#define neof (ch != '\0')  

  fetch;
  if (ch != '$') fail;
  fetch;
  if (digit) strchr(fname, '$')[0] = ch; else fail;
  fetch;
  if (!white) fail;
  do fetch; while (white);
  while (neof)
  {
    int i, y = 0, x = 0;
    while (digit) { x *= 10; x += (ch-'0'); fetch; }
    if (ch == '.')
    {
      while (ch == '.') fetch;
      while (digit) { y *= 10; y += (ch-'0'); fetch; }
    }
    else
      y=x;
    while (white) fetch;

    char buffer[0x1000], *bufferd;
    i=0;
    while (i<sizeof(buffer)-1 && ch!='\n') { buffer[i]=ch; fetch; i++; }
    while (nwhite) fetch;
    buffer[i]='\0';
    bufferd = strdup(buffer);
    for (; x<=y && x<=max_trigger_no; x++)
      triggers[x] = bufferd;
    while (white) fetch; 
  }

  FILE* file = fopen(fname, "r");
  if (!file)
    return EXIT_FAILURE;
 
  daemon(0, 0);
  nice(99);
  
  struct input_event ev;
  while (fread(&ev, sizeof(ev), 1, file) > 0)
  {
    if (ev.value)
    {
      if (ev.code <= max_trigger_no)
      if (triggers[ev.code])
        system(triggers[ev.code]);
    }
  }
  return EXIT_SUCCESS;
}

/* vim:set ts=2 sw=2 et: */
