#include "../include/myBigChars.h"

#include <stdio.h>
#include <string.h>

int
bc_printA (const char str)
{
  if (printf ("\033(0%c\033(B", str) != strlen ("\033(0c\033(B"))
    {
      return -1;
    }

  return 0;
}
