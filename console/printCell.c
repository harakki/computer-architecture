#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"

void
printCell (int address)
{
  if (address >= 0 && address < RAM_SIZE)
    {
      int sign = 0;
      int command = 0;
      int operand = 0;

      const int data = random_access_memory[address];

      sc_commandDecode (data, &sign, &command, &operand);

      printf ("%c%02X%02X", sign ? '-' : '+', command, operand);
    }
  else
    {
      printf ("!%04i", address);
    }
}
