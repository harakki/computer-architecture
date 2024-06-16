#include "console.h"

#include "../include/myBigChars.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printTui (void)
{
  mt_clrscr ();

  bc_box (1, 1, 61, 15, DEFAULT, DEFAULT, "Memory", RED, DEFAULT);
  bc_box (62, 1, 85, 3, DEFAULT, DEFAULT, "Accumulator", RED, DEFAULT);
  bc_box (86, 1, 108, 3, DEFAULT, DEFAULT, "Flags", RED, DEFAULT);
  bc_box (62, 4, 85, 6, DEFAULT, DEFAULT, "Command counter", RED, DEFAULT);
  bc_box (86, 4, 108, 6, DEFAULT, DEFAULT, "Command", RED, DEFAULT);
  bc_box (62, 7, 108, 18, DEFAULT, DEFAULT, "Editable cell (enlarged)", RED,
          WHITE);
  bc_box (1, 16, 61, 18, DEFAULT, DEFAULT, "Editable cell (formats)", RED,
          WHITE);
  bc_box (1, 19, 66, 25, DEFAULT, DEFAULT, "Processors cache", GREEN, WHITE);
  bc_box (67, 19, 77, 25, DEFAULT, DEFAULT, "IN--OUT", GREEN, WHITE);
  bc_box (78, 19, 108, 25, DEFAULT, DEFAULT, "Keys", GREEN, WHITE);

  for (int i = 0; i < 128; ++i)
    {
      printCell (i, DEFAULT, DEFAULT);
    }

  /* Show selected cell graphically */
  printCell (selected_cell, BLACK, WHITE);

  mt_setDefaultColor ();

  printDecodedCommand (random_access_memory[selected_cell]);
  printAccumulator ();
  printFlags ();
  printCounters ();
  printCommand ();
  printBigCell ();
  printCache ();
  printTerm ();
  printKeys ();

  /* Set cursor under computer state display */
  mt_gotoXY (1, 26);

  mt_setFgColor (GREEN);
}
