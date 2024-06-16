#include "../include/mySimpleComputer.h"

void
sc_cacheInit (void)
{
  for (int i = 0; i < CACHE_SIZE; ++i)
    {
      for (int j = 0; j < CACHE_ROW_SIZE; ++j)
        {
          l1_cache[i].data[j] = 0;
          l1_cache[i].address = -1;
          l1_cache[i].last_access = 0;
        }
    }
}
