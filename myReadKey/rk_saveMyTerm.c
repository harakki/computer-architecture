#include "../include/myReadKey.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int
rk_saveMyTerm (void)
{
  FILE *term_file = fopen ("term-backup.tmp", "wb");
  struct termios termios_backup;

  if (term_file == NULL)
    {
      return -1;
    }

  if (tcgetattr (fileno (stdin), &termios_backup) == -1)
    {
      fclose (term_file);
      return -1;
    }

  if (fwrite (&termios_backup, sizeof (termios_backup), 1, term_file) != 1)
    {
      fclose (term_file);
      return -1;
    }

  fclose (term_file);
  return 0;
}