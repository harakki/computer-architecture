#include "console.h"

#include <stdio.h>

void
printDecodedCommand (int value)
{
  printf ("dec: %05d | oct: %05o | hex: %04X    bin: ", value, value, value);

  for (size_t i = 15; i; i--)
    {
      putchar ('0' + ((value >> (i - 1)) & 1));
    }
}
