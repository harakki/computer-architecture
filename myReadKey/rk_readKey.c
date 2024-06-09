#include "../include/myReadKey.h"

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int
rk_readKey (enum keys *key)
{
  struct termios termios_backup;
  char buf[15];
  int read_size;

  if (tcgetattr (fileno (stdin), &termios_backup) != 0
      || rk_myTermRegime (0, 0, 1, 0, 1) != 0
      || (read_size = read (fileno (stdin), buf, 15)) < 0)
    {
      return -1;
    }

  buf[read_size] = '\0';

  if (buf[0] == 'l' || buf[0] == 'L')
    {
      *key = LOAD_KEY;
    }
  else if (buf[0] == 's' || buf[0] == 'S')
    {
      *key = SAVE_KEY;
    }
  else if (buf[0] == 'r' || buf[0] == 'R')
    {
      *key = RUN_KEY;
    }
  else if (buf[0] == 't' || buf[0] == 'T')
    {
      *key = STEP_KEY;
    }
  else if (buf[0] == 'i' || buf[0] == 'I')
    {
      *key = RESET_KEY;
    }
  else if (buf[0] == 'q' || buf[0] == 'Q')
    {
      *key = QUIT_KEY;
    }
  else if (buf[0] == '5')
    {
      *key = F5_KEY;
    }
  else if (buf[0] == '6')
    {
      *key = F6_KEY;
    }
  else if (buf[0] == '\n')
    {
      *key = ENTER_KEY;
    }
  else if (buf[0] == '\033')
    {
      if (strcmp (buf, "\033[15~") == 0)
        {
          *key = F5_KEY;
        }
      else if (strcmp (buf, "\033[17~") == 0)
        {
          *key = F6_KEY;
        }
      else if (strcmp (buf, "\033[A") == 0)
        {
          *key = UP_ARROW_KEY;
        }
      else if (strcmp (buf, "\033[B") == 0)
        {
          *key = DOWN_ARROW_KEY;
        }
      else if (strcmp (buf, "\033[C") == 0)
        {
          *key = RIGHT_ARROW_KEY;
        }
      else if (strcmp (buf, "\033[D") == 0)
        {
          *key = LEFT_ARROW_KEY;
        }
      /* ! DO NOT DELETE: it may cause program to close due to the similar
       * start of '\033' during fast processing (holding arrow key) */
      else if (strcmp (buf, "\033") == 0)
        {
          *key = ESC_KEY;
        }
    }
  else
    {
      *key = UNKNOWN_KEY;
    }

  return tcsetattr (fileno (stdin), TCSANOW, &termios_backup) != 0 ? -1 : 0;
}