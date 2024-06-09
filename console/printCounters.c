#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"

void
printCounters (void)
{
  printf ("T: %03d    IC: +%04X", idle_clock_counter, command_counter);
}
