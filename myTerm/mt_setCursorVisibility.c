#include "../include/myTerm.h"

#include <stdio.h>
#include <unistd.h>

int
mt_setCursorVisibility (int value)
{
  char buf[16];
  const int to_write = snprintf (buf, sizeof (buf), "%s",
                                 value ? "\033[?12;25h" : "\033[?25l");

  const int written = write (1, buf, to_write);

  if (written != to_write)
    {
      return -1;
    }

  return 0;
}
