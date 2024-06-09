#include "../include/myBigChars.h"

#include <stddef.h>

size_t
bc_strlen (const char *str)
{
  size_t string_length = 0;

  if (str == NULL)
    {
      return 0;
    }

  while (*str)
    {
      if ((*str & 0xC0) != 0x80)
        {
          string_length++;
        }

      str++;
    }

  return string_length;
}
