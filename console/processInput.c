#include "console.h"

#include <signal.h>
#include <stdio.h>

#include "../include/myReadKey.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
processInput (enum keys key, int *exit_flag)
{
  switch (key)
    {
    case F5_KEY:
      {
        printf ("[ACCUMULATOR EDIT] ");

        int input;

        mt_gotoXY (79, 2);

        if (scanf ("%4X", &input) != 1)
          {
            printf ("Not a number\n");
          }

        sc_accumulatorSet (input);
        break;
      }
    case F6_KEY:
      {
        printf ("[COUNTER EDIT] ");

        int input;

        mt_gotoXY (78, 5);

        if (scanf ("%4X", &input) != 1)
          {
            printf ("Not a number\n");
          }

        sc_icounterSet (input);
        break;
      }
    case ENTER_KEY:
      {
        printf ("[CELL EDIT] ");

        char raw_input[7];
        int value;
        char sign;
        int command;
        int operand;

        mt_gotoXY ((selected_cell % 10 + 1) * 6 - 4, selected_cell / 10 + 2);

        if (fgets (raw_input, sizeof (raw_input), stdin) == NULL
            || sscanf (raw_input, "%c%02X%02X", &sign, &command, &operand)
                   == -1
            || sc_commandEncode (sign == '+' ? 0 : 1, command, operand, &value)
                   == -1
            || sc_memorySet (selected_cell, value) == -1)
          {
            perror ("Not a number");
          }

        mt_termEnqueue (selected_cell, 1);
        break;
      }
    case LEFT_ARROW_KEY:
      {
        selected_cell == 0 ? selected_cell = 127 : selected_cell--;
        break;
      }
    case RIGHT_ARROW_KEY:
      {
        selected_cell == 127 ? selected_cell = 0 : selected_cell++;
        break;
      }
    case UP_ARROW_KEY:
      {
        selected_cell = selected_cell < 10 ? (selected_cell + 120 - 1) % 130
                                           : selected_cell - 10;
        if (selected_cell > 127)
          {
            selected_cell = selected_cell - 10;
          }
        break;
      }
    case DOWN_ARROW_KEY:
      {
        selected_cell = selected_cell > 127 - 10 ? selected_cell - 120 + 1
                                                 : selected_cell + 10;

        if (selected_cell > 127)
          {
            selected_cell = selected_cell + 10;
          }

        break;
      }
    case LOAD_KEY:
      {
        printf ("[MEMORY LOADING] ");

        char filename[64];

        if (scanf ("%63s", filename) != 1)
          {
            perror ("Not a string");
          }
        printf (sc_memoryLoad (filename) == -1 ? "ERROR" : "SUCCESS");
        break;
      }
    case SAVE_KEY:
      {
        printf ("[MEMORY SAVING] ");

        char filename[64];

        if (scanf ("%63s", filename) != 1)
          {
            perror ("Not a string");
          }
        printf (sc_memorySave (filename) == -1 ? "ERROR" : "SUCCESS");
        break;
      }
    case RUN_KEY:
      {
        sc_regInit ();
        sc_regSet (CLOCK_PULSES_IGNORE, 0);
        raise (SIGALRM);
        break;
      }
    case STEP_KEY:
      {
        CU ();
        sc_icounterGet ((int *)&selected_cell);
        break;
      }
    case RESET_KEY:
      {
        sc_reset ();
        break;
      }
    case QUIT_KEY:
    case ESC_KEY:
      *exit_flag = 1;
      break;
    default:
      break;
    }
}
