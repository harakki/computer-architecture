#include "../include/myTerm.h"

#include <string.h>
#include <unistd.h>

int
mt_clrscr (void)
{
  const char *buf = "\033[H\033[2J";

  const int written = write (1, buf, strlen (buf));

  if (written != (int)strlen (buf))
    {
      return -1;
    }

  return 0;
}
