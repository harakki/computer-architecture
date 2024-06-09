#include "../include/myTerm.h"

#include <stdio.h>
#include <unistd.h>

int
mt_setFgColor (enum colors color)
{
  char buf[16];

  const int to_write
      = color == DEFAULT
            ? snprintf (buf, sizeof (buf), "\033[39m")
            : snprintf (buf, sizeof (buf), "\033[38;5;%im", color);

  const int written = write (1, buf, to_write);

  if (written != to_write)
    {
      return -1;
    }

  return 0;
}
