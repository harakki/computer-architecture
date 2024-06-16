#include "../include/mySimpleComputer.h"

#include <stdbool.h>
#include <time.h>

int sc_cacheGetOldest (void);

void
sc_cacheUpdate (int address, int *value)
{
  static int current_index = 0;
  static int rows_filled = 0;

  if (update_l1_cache)
    {
      current_index = 0;
      rows_filled = 0;
      update_l1_cache = false;
    }

  *value = random_access_memory[address];
  int line_address = address / 10 * 10;
  int in_cache = false;

  for (int i = 0; i < CACHE_SIZE && !in_cache; ++i)
    {
      if (l1_cache[i].address == line_address)
        {
          in_cache = true;
          current_index = i;
        }
    }

  if (!in_cache)
    {
      if (rows_filled < CACHE_SIZE)
        {
          current_index = rows_filled++;
        }
      else
        {
          current_index = sc_cacheGetOldest ();
        }

      l1_cache[current_index].address = line_address;
    }

  for (int j = 0; j < CACHE_ROW_SIZE; ++j)
    {
      l1_cache[current_index].data[j] = random_access_memory[line_address + j];
    }

  l1_cache[current_index].last_access = time (NULL);
}

int
sc_cacheGetOldest (void)
{
  int oldest_record = 0;
  time_t last_time_used = l1_cache[0].last_access;
  for (int i = 1; i < CACHE_SIZE; ++i)
    {
      if (l1_cache[i].last_access < last_time_used)
        {
          last_time_used = l1_cache[i].last_access;
          oldest_record = i;
        }
    }
  return oldest_record;
}
