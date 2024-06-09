#include "../include/mySimpleComputer.h"

int
sc_commandValidate (int command)
{
  const int cpu_commands[]
      = { 0x00, 0x01, 0x0A, 0x0B, 0x14, 0x15, 0x1E, 0x1F, 0x20, 0x21,
          0x28, 0x29, 0x2A, 0x2B, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
          0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42,
          0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4c };

  int left = 0;
  int right = sizeof (cpu_commands) / sizeof (cpu_commands[0]) - 1;

  while (left <= right)
    {
      const int middle = left + (right - left) / 2;
      if (cpu_commands[middle] == command)
        {
          return 0;
        }
      else if (cpu_commands[middle] < command)
        {
          left = middle + 1;
        }
      else
        {
          right = middle - 1;
        }
    }

  return -1;
}
