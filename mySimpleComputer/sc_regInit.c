#include "../include/mySimpleComputer.h"

int
sc_regInit (void)
{
  flag_register = 0;

  sc_regSet (CLOCK_PULSES_IGNORE, 1);

  return 0;
}
