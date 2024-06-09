#include "../include/myBigChars.h"

#include <stdio.h>

#include "../include/myTerm.h"

int
bc_printBigChar (int *big, int x, int y, enum colors bg, enum colors fg)
{
  int value;

  mt_setFgColor (bg);
  mt_setBgColor (fg);

  for (int i = 0; i < BIG_CHAR_WIDTH; ++i)
    {
      for (int j = 0; j < BIG_CHAR_HEIGHT; ++j)
        {
          if (bc_getBigCharPosition (big, i, j, &value))
            {
              return -1;
            }

          mt_gotoXY (x + i, y + j);
          value ? bc_printA (FRAME_BLACK_BOX) : printf (" ");
        }
    }

  mt_setDefaultColor ();

  return 0;
}
