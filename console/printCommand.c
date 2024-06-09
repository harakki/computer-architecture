#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printCommand (void)
{
  mt_calculatePosition (0, 1, 1, 4, 92);

  int value = 0;
  int sign;
  int command;
  int operand;

  sc_memoryGet (command_counter, &value);
  sc_commandDecode (value, &sign, &command, &operand);

  printf ("%c %02X : %02X", sign ? '-' : '+', command, operand);

  if (sc_commandValidate (command) != 0)
    {
      printf (" !");
    }
}
