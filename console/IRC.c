#include "console.h"

#include <signal.h>
#include <unistd.h>

#include "../include/myReadKey.h"
#include "../include/mySimpleComputer.h"

void
IRC (int signum)
{
  switch (signum)
    {
    case SIGALRM:
      {
        int flag_clock_pulses_ignore;

        sc_regGet (CLOCK_PULSES_IGNORE, &flag_clock_pulses_ignore);

        if (flag_clock_pulses_ignore == 1)
          {
            return;
          }

        sc_icounterGet ((int *)&selected_cell);
        printTui ();
        CU ();
        ualarm (500000, 500000);
        rk_myTermRegime (0, 1, 1, 0, 0);
        break;
      }
    case SIGUSR1:
      {
        sc_reset ();
        break;
      }
    default:
      break;
    }
}