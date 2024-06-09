#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"

void
printAccumulator (void)
{
  int sign;
  int command;
  int operand;

  sc_commandDecode (accumulator, &sign, &command, &operand);

  printf ("sc: %c%02X%02X hex: %04X", sign ? '-' : '+', command, operand,
          accumulator);
}
