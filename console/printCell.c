#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printCell (int address, enum colors fg, enum colors bg)
{
  mt_setFgColor (fg);
  mt_setBgColor (bg);

  mt_calculatePosition (address, 6, 10, 1, 1);

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
