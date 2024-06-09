#include "console.h"

#include <stdio.h>

#include "../include/myTerm.h"

void
printDecodedCommand (int value)
{
  mt_calculatePosition (0, 1, 1, 16, 1);

  printf ("dec: %05d | oct: %05o | hex: %04X    bin: ", value, value, value);

  for (size_t i = 15; i; i--)
    {
      putchar ('0' + ((value >> (i - 1)) & 1));
    }
}
