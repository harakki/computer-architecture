#include "../include/mySimpleComputer.h"

#include <stdio.h>

int
sc_memorySave (char *filename)
{

  if (filename == NULL)
    {
      return -1;
    }

  FILE *file = fopen (filename, "wb");

  if (file == NULL)
    {
      return -1;
    }

  if (fwrite (random_access_memory, sizeof (unsigned short),
              sizeof (random_access_memory) / sizeof (unsigned short), file)
      != sizeof (random_access_memory) / sizeof (unsigned short))
    {
      fclose (file);

      return -1;
    }

  fclose (file);

  return 0;
}
