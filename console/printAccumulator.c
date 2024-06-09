#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printAccumulator (void)
{
  int sign;
  int command;
  int operand;

  mt_calculatePosition (0, 1, 1, 1, 63);

  sc_commandDecode (accumulator, &sign, &command, &operand);

  printf ("sc: %c%02X%02X hex: %04X", sign ? '-' : '+', command, operand,
          accumulator);
}
