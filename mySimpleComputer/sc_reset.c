#include "../include/mySimpleComputer.h"

#include "../include/myTerm.h"

void
sc_reset (void)
{
  selected_cell = 0;
  idle_clock_counter = 0;
  sc_memoryInit ();
  sc_accumulatorInit ();
  sc_regInit ();
  sc_icounterInit ();
  mt_termInit ();
}
