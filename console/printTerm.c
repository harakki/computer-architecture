#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printTerm (void)
{
  int address;
  int input;
  int data;

  int sign;
  int command;
  int operand;

  cell_history_item_t history[HISTORY_SIZE];

  mt_termDequeue (history);

  for (int i = 0; i < HISTORY_SIZE; ++i)
    {
      address = history[i].address;
      input = history[i].input_type;
      data = history[i].data;

      sc_commandDecode (data, &sign, &command, &operand);

      mt_calculatePosition (i, 9, 1, 19, 67);

      printf ("%02X%c %c%02X%02X", address, input ? '<' : '>',
              sign ? '-' : '+', command, operand);
    }
}
