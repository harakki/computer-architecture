#include "../include/myBigChars.h"

int
bc_setBigCharPosition (int *big, int x, int y, int value)
{
  int row_index = y / BIG_CHAR_SIZE;
  int bit_position
      = (y % BIG_CHAR_SIZE) * BIG_CHAR_WIDTH + (BIG_CHAR_WIDTH - 1 - x);

  if (x < 0 || y < 0 || x >= BIG_CHAR_WIDTH || y >= BIG_CHAR_HEIGHT)
    {
      return -1;
    }

  if (value)
    {
      big[row_index] |= (1 << bit_position);
    }
  else
    {
      big[row_index] &= ~(1 << bit_position);
    }

  return 0;
}
