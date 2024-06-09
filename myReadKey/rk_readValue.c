#include "../include/myReadKey.h"

#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int
rk_readValue (int *value, int timeout)
{
  struct termios termios_backup;
  struct termios new_termios;
  char input[32];

  if (tcgetattr (fileno (stdin), &termios_backup) != 0)
    {
      perror ("tcgetattr");
      return -1;
    }

  new_termios = termios_backup;
  new_termios.c_lflag &= ~(ICANON | ECHO);

  if (tcsetattr (fileno (stdin), TCSANOW, &new_termios) != 0)
    {
      perror ("tcsetattr");
      return -1;
    }

  struct pollfd fds;
  fds.fd = fileno (stdin);
  fds.events = POLLIN;

  const int poll_result = poll (&fds, 1, timeout);
  if (poll_result == -1)
    {
      perror ("poll");
      tcsetattr (fileno (stdin), TCSANOW, &termios_backup);
      return -1;
    }

  if (poll_result == 0)
    {
      fprintf (stderr, "Timeout occurred.\n");
      tcsetattr (fileno (stdin), TCSANOW, &termios_backup);
      return -1;
    }

  const int read_bytes = read (fileno (stdin), input, sizeof (input) - 1);
  if (read_bytes < 0)
    {
      perror ("read");
      tcsetattr (fileno (stdin), TCSANOW, &termios_backup);
      return -1;
    }

  input[read_bytes] = '\0';

  if (tcsetattr (fileno (stdin), TCSANOW, &termios_backup) != 0)
    {
      perror ("tcsetattr");
      return -1;
    }

  *value = atoi (input);

  return 0;
}