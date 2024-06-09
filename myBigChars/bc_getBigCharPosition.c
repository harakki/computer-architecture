#include "../include/myBigChars.h"

int
bc_getBigCharPosition (int *big, int x, int y, int *value)
{
  int row_index = y / BIG_CHAR_SIZE;
  int bit_position
      = (y % BIG_CHAR_SIZE) * BIG_CHAR_WIDTH + (BIG_CHAR_WIDTH - 1 - x);

  if (x < 0 || y < 0 || x >= BIG_CHAR_WIDTH || y >= BIG_CHAR_HEIGHT)
    {
      return -1;
    }

  *value = big[row_index] & (1 << bit_position) ? 1 : 0;

  return 0;
}
