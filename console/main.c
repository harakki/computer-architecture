#include <stdio.h>
#include <unistd.h>

#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"
#include "console.h"

int
main (void)
{
  /*!
   * Change the output stream to unbuffered (line buffered by default) on
   * POSIX-compatible systems
   */
  setbuf (stdout, NULL);

  if (!isatty (fileno (stdout)))
    {
      perror ("Terminal initialization failed");
      return -1;
    }

  int rows;
  int cols;

  mt_getScreenSize (&rows, &cols);

#if defined NDEBUG
  if (rows < 25 || cols < 109)
    {
      fprintf (stderr, "Terminal initialization failed: Small viewport size"
                       " (requires at least 110x25)\n");
      return -1;
    }
#endif

  /* Computer initialization */
  sc_reset ();

  int flag_clock_pulses_ignore;

  sc_regGet (CLOCK_PULSES_IGNORE, &flag_clock_pulses_ignore);

  printTui ();

  /* Set cursor to the end of output to display shell correctly */
  mt_gotoXY (1, rows);
  mt_setDefaultColor ();

  return 0;
}
