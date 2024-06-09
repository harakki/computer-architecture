#include "../include/myBigChars.h"

#include <unistd.h>

int
bc_readBigChar (int fd, int *big, int need_count, int *count)
{
  *count = 0;

  for (int i = 0; i < need_count; ++i)
    {
      if (read (fd, &big[i * 2], sizeof (uint32_t)) == -1
          || read (fd, &big[i * 2 + 1], sizeof (uint32_t)) == -1)
        {
          *count = 0;

          return -1;
        }

      (*count)++;
    }

  return 0;
}
