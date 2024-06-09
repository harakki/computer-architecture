#include "console.h"

#include <stdio.h>
#include <unistd.h>

#include "../include/myReadKey.h"
#include "../include/mySimpleComputer.h"
#include "../include/myTerm.h"

void
CU (void)
{
  int sign;
  int command;
  int operand;

  int memory_data;
  int accumulator_data;
  int command_counter_data;

  sc_accumulatorGet (&accumulator_data);
  sc_icounterGet (&command_counter_data);

  if (sc_memoryGet (command_counter_data, &memory_data) != 0)
    {
      sc_regSet (OUT_OF_MEMORY, 1);
      sc_regSet (CLOCK_PULSES_IGNORE, 1);
      return;
    }

  if (sc_commandDecode (memory_data, &sign, &command, &operand) != 0)
    {
      sc_regSet (INCORRECT_COMMAND, 1);
      sc_regSet (CLOCK_PULSES_IGNORE, 1);
      return;
    }

  switch (command)
    {
    case NOP:
      break;
    case CPUINFO:
      printf ("github.com/harakki");
      break;

    /* Input/Output */
    case READ:
      {
        int value;

        printf ("[Enter data in %d cell] ", operand);
        rk_restoreMyTerm ();
        do
          {
            while (scanf ("%d", &value) == -1)
              ;
          }
        while (sc_memorySet (operand, value) != 0);

        mt_termEnqueue (operand, 1);
        break;
      }
    case WRITE:
      {
        char buf[32];

        if (sc_memoryGet (operand, &memory_data) != 0)
          {
            sc_regSet (OUT_OF_MEMORY, 1);
            sc_regSet (CLOCK_PULSES_IGNORE, 1);
            return;
          }
        sscanf (buf, "%d", &memory_data);

        mt_termEnqueue (operand, 0);
        break;
      }

    /* Loading/Unloading into the battery */
    case LOAD:
      {
        if (sc_memoryGet (operand, &memory_data) != 0)
          {
            sc_regSet (OUT_OF_MEMORY, 1);
            sc_regSet (CLOCK_PULSES_IGNORE, 1);
            return;
          }
        sc_accumulatorSet (memory_data);
        break;
      }
    case STORE:
      sc_memorySet (operand, accumulator_data);
      break;

    /* Arithmetic */
    case ADD:
    case SUB:
    case DIVIDE:
    case MUL:
      {
        if (ALU (command, operand) != 0)
          {
            sc_regSet (CLOCK_PULSES_IGNORE, 1);
          }
        break;
      }

    /* Control transfer */
    case JUMP:
      sc_icounterSet (operand);
      return;
    case JNEG:
      if (accumulator_data < 0)
        {
          sc_icounterSet (operand);
          return;
        }
      break;
    case JZ:
      if (accumulator_data == 0)
        {
          sc_icounterSet (operand);
          return;
        }
      break;
    case HALT:
      sc_regSet (CLOCK_PULSES_IGNORE, 1);
      break;

    /* Extensions */
    case JNS:
      {
        if (accumulator_data > 0)
          {
            sc_icounterSet (operand);
            return;
          }
        break;
      }
    case JP:
      {
        if (accumulator_data % 2 == 0)
          {
            sc_icounterSet (operand);
            return;
          }
        break;
      }
    case JNP:
      {
        if (accumulator_data % 2 != 0)
          {
            sc_icounterSet (operand);
            return;
          }
        break;
      }
    default:
      sc_regSet (INCORRECT_COMMAND, 1);
      sc_regSet (CLOCK_PULSES_IGNORE, 1);
      return;
    }

  if (sc_icounterSet (command_counter_data + 1) != 0)
    {
      sc_regSet (OUT_OF_MEMORY, 1);
      sc_regSet (CLOCK_PULSES_IGNORE, 1);
    }
}
