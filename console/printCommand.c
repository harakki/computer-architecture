#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printCommand (void)
{
  mt_calculatePosition (0, 1, 1, 4, 92);

  int value = random_access_memory[command_counter];
  int sign;
  int command;
  int operand;

  sc_commandDecode (value, &sign, &command, &operand);

  printf ("%c %02X : %02X", sign ? '-' : '+', command, operand);

  if (sc_commandValidate (command) != 0)
    {
      printf (" !");
    }
}
