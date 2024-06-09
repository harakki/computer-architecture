#include "../include/myTerm.h"

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

void
mt_getScreenSize (int *rows, int *cols)
{
  struct winsize term;

  ioctl (STDOUT_FILENO, TIOCGWINSZ, &term);

  *rows = term.ws_row;
  *cols = term.ws_col;
}
