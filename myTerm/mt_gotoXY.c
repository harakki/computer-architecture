#include "../include/myTerm.h"

#include <stdio.h>
#include <unistd.h>

int
mt_gotoXY (int x, int y)
{
  char buf[16];
  const int to_write = snprintf (buf, sizeof (buf), "\033[%i;%iH", y, x);

  const int written = write (1, buf, to_write);

  if (written != to_write)
    {
      return -1;
    }

  return 0;
}
