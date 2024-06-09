#include "console.h"

#include <stdio.h>

#include "../include/myBigChars.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printBigCell (void)
{
  const int x = 63;
  const int y = 9;

  int value;
  int sign = 0;
  int command = 0;
  int operand = 0;

  sc_memoryGet (selected_cell, &value);

  sc_commandDecode (value, &sign, &command, &operand);

  /* Print sign */
  bc_printBigChar (char_patterns[16 + sign], x, y, DEFAULT, DEFAULT);

  /* Print command */
  for (int i = 0; i < 2; ++i)
    {
      int glyph = command >> ((1 - i) * 4) & 0xF;

      bc_printBigChar (char_patterns[glyph],
                       x + (BIG_CHAR_WIDTH + 1) * (i + 1), y, DEFAULT,
                       DEFAULT);
    }

  /* Print operand */
  for (int i = 0; i < 2; ++i)
    {
      int glyph = operand >> ((1 - i) * 4) & 0xF;

      bc_printBigChar (char_patterns[glyph],
                       x + (BIG_CHAR_WIDTH + 1) * (i + 3), y, DEFAULT,
                       DEFAULT);
    }

  mt_gotoXY (70, 17);
  mt_setFgColor (BLUE);

  printf ("Number of cell being edited: %03d", selected_cell);

  mt_setDefaultColor ();
}
