#include "../include/myTerm.h"

#include <string.h>
#include <unistd.h>

int
mt_setDefaultColor (void)
{
  const char *buf = "\033[39m\033[49m";

  const int written = write (1, buf, strlen (buf));

  if (written != (int)strlen (buf))
    {
      return -1;
    }

  return 0;
}
