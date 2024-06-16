#include "console.h"

#include <stdio.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
printCache (void)
{
  for (int i = 0; i < CACHE_SIZE; ++i)
    {
      mt_gotoXY (2, 20 + i);

      if (l1_cache[i].address == -1)
        {
          printf ("-1:  !#### !#### !#### !#### !#### !#### !#### !#### !#### "
                  "!####");
        }
      else
        {
          printf ("%03i: ", l1_cache[i].address);

          for (int j = 0; j < CACHE_ROW_SIZE; ++j)
            {
              const int value = l1_cache[i].data[j];
              int sign;
              int command;
              int operand;

              sc_commandDecode (value, &sign, &command, &operand);

              printf ("%c%02X%02X", sign ? '-' : '+', command, operand);

              if (j < CACHE_ROW_SIZE - 1)
                {
                  printf (" ");
                }
            }
        }
    }
}
