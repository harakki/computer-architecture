#include "console.h"

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printTui (void)
{
  mt_clrscr ();

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
  printTerm ();
  printKeys ();

  /* Set cursor under computer state display */
  mt_gotoXY (1, 26);

  mt_setFgColor (GREEN);
}
