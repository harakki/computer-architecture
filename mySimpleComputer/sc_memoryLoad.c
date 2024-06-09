#include "../include/mySimpleComputer.h"

#include <stdio.h>

int
sc_memoryLoad (char *filename)
{
  if (filename == NULL)
    {
      return -1;
    }

  FILE *file = fopen (filename, "rb");

  if (file == NULL)
    {
      return -1;
    }

  if (fread (random_access_memory, sizeof (unsigned short),
             sizeof (random_access_memory) / sizeof (unsigned short), file)
      != sizeof (random_access_memory) / sizeof (unsigned short))
    {
      fclose (file);

      return -1;
    }

  fclose (file);

  return 0;
}
