#include "console.h"

#include <stdio.h>

#include "../include/myTerm.h"

void
printKeys (void)
{
  mt_gotoXY (79, 20);
  printf ("l - load  s - save  i - reset");

  mt_gotoXY (79, 21);
  printf ("r - run   t - step");

  mt_gotoXY (79, 22);
  printf ("ESC - exit");

  mt_gotoXY (79, 23);
  printf ("F5 - accumulator");

  mt_gotoXY (79, 24);
  printf ("F6 - instruction counter");
}
