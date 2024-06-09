#include "../include/myTerm.h"

#include <string.h>
#include <unistd.h>

int
mt_delLine (void)
{
  const char *buf = "\033[M";

  const int written = write (1, buf, strlen (buf));

  if (written != (int)strlen (buf))
    {
      return -1;
    }

  return 0;
}
