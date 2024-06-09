#include "../include/myReadKey.h"

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int
rk_myTermRegime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios saved_termios;

  if (tcgetattr (fileno (stdin), &saved_termios) == -1)
    {
      return -1;
    }

  if (regime == 0)
    {
      saved_termios.c_lflag &= ~ICANON;
      saved_termios.c_cc[VTIME] = vtime;
      saved_termios.c_cc[VMIN] = vmin;

      if (echo == 0)
        {
          saved_termios.c_lflag &= ~ECHO;
        }
      else if (echo == 1)
        {
          saved_termios.c_lflag |= ECHO;
        }
      else
        {
          return -1;
        }

      if (sigint == 0)
        {
          saved_termios.c_lflag &= ~ISIG;
        }
      else if (sigint == 1)
        {
          saved_termios.c_lflag |= ISIG;
        }
      else
        {
          return -1;
        }
    }
  else if (regime == 1)
    {
      saved_termios.c_lflag |= ICANON;
    }
  else
    {
      return -1;
    }

  if (tcsetattr (fileno (stdin), TCSANOW, &saved_termios) == -1)
    {
      return -1;
    }

  return 0;
}