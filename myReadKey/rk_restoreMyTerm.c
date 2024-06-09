#include "../include/myReadKey.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int
rk_restoreMyTerm (void)
{
  FILE *term_file = fopen ("term-backup.tmp", "rb");
  struct termios termios_backup;

  if (term_file == NULL)
    {
      return -1;
    }

  if (fread (&termios_backup, sizeof (termios_backup), 1, term_file) != 1)
    {
      fclose (term_file);
      return -1;
    }

  if (tcsetattr (fileno (stdin), TCSANOW, &termios_backup) == -1)
    {
      fclose (term_file);
      return -1;
    }

  fclose (term_file);
  return 0;
}