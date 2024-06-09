#include "console.h"

#include "../include/mySimpleComputer.h"

int
ALU (int command, int operand)
{
  int accumulator_data;
  int command_counter_data;
  int memory_data;

  sc_accumulatorGet (&accumulator_data);
  sc_icounterGet (&command_counter_data);

  if (sc_memoryGet (operand, &memory_data) == -1)
    {
      sc_regSet (OUT_OF_MEMORY, 1);
      return -1;
    }

  switch (command)
    {
    case ADD:
      {
        if (sc_accumulatorSet (accumulator_data + memory_data) == -1)
          {
            sc_regSet (MEMORY_CELL_OVERFLOW, 1);
            return -1;
          }
        break;
      }
    case SUB:
      {
        if (sc_accumulatorSet (accumulator_data - memory_data) == -1)
          {
            sc_regSet (MEMORY_CELL_OVERFLOW, 1);
            return -1;
          }
        break;
      }
    case DIVIDE:
      {
        if (memory_data == 0)
          {
            sc_regSet (DIVISION_BY_ZERO, 1);
            return -1;
          }
        if (sc_accumulatorSet (accumulator_data / memory_data) == -1)
          {
            sc_regSet (MEMORY_CELL_OVERFLOW, 1);
            return -1;
          }
        break;
      }
    case MUL:
      {
        if (sc_accumulatorSet (accumulator_data * memory_data) == -1)
          {
            sc_regSet (MEMORY_CELL_OVERFLOW, 1);
            return -1;
          }
        break;
      }
    default:
      return -1;
    }

  return 0;
}
