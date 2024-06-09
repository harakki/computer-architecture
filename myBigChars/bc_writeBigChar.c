#include "../include/myBigChars.h"

#include <stdint.h>
#include <unistd.h>

int
bc_writeBigChar (int fd, int *font_bitmap, int symbols_amount)
{
  const int big_char_size = 8 * sizeof (uint32_t);
  const int total_size = symbols_amount * big_char_size;

  if (write (fd, font_bitmap, total_size) == -1)
    {
      return -1;
    }

  return 0;
}
