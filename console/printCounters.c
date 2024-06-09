#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printCounters (void)
{
  mt_calculatePosition (0, 1, 1, 4, 63);

  printf ("T: %03d    IC: +%04X", idle_clock_counter, command_counter);
}
