#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/myBigChars.h"
#include "../include/mySimpleComputer.h"
#include "console.h"

int
main (const int argc, char *argv[])
{
  /*!
   * Change the output stream to unbuffered (line buffered by default) on
   * POSIX-compatible systems
   */
  setbuf (stdout, NULL);

  /* Reading font file for big chars */
  const char *font_file = (argc > 1) ? argv[1] : "font.bin";
  const int fd = open (font_file, O_RDONLY);

  if (fd == -1)
    {
      perror (font_file);
      return -1;
    }

  const int bytes_read = read (fd, char_patterns, sizeof (char_patterns));

  if (bytes_read != sizeof (char_patterns))
    {
      fprintf (stderr, "%s: File data is not valid\n", font_file);
      return -1;
    }

  close (fd);

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

  rk_saveMyTerm ();

  int exit_flag = 0;
  int flag_clock_pulses_ignore;
  enum keys key;

  while (!exit_flag)
    {
      sc_regGet (CLOCK_PULSES_IGNORE, &flag_clock_pulses_ignore);

      if (!flag_clock_pulses_ignore)
        {
          continue;
        }

      printTui ();

      rk_readKey (&key);

      processInput (key, &exit_flag);
    }

  /* Set cursor to the end of output to display shell correctly */
  mt_gotoXY (1, rows);
  mt_setDefaultColor ();

  return 0;
}
