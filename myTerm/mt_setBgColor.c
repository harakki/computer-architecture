#include "../include/myTerm.h"

#include <stdio.h>
#include <unistd.h>

int
mt_setBgColor (enum colors color)
{
  char buf[16];

  const int to_write
      = color == DEFAULT
            ? snprintf (buf, sizeof (buf), "\033[49m")
            : snprintf (buf, sizeof (buf), "\033[48;5;%im", color);

  const int written = write (1, buf, to_write);

  if (written != to_write)
    {
      return -1;
    }

  return 0;
}
