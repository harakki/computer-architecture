#ifndef MY_SIMPLE_COMPUTER_H_
#define MY_SIMPLE_COMPUTER_H_

#include <stdbool.h>
#include <stdint.h>

enum flags
{
  MEMORY_CELL_OVERFLOW, /* P "overflow during operation" */
  DIVISION_BY_ZERO,     /* 0 */
  OUT_OF_MEMORY,        /* M "going beyond boundaries of memory" */
  CLOCK_PULSES_IGNORE,  /* T */
  INCORRECT_COMMAND     /* E */
};

enum sizes
{
  RAM_SIZE = 128,
  FLAGS_REG_SIZE = 5,
  FLAGS_AMOUNT = 5,
  CACHE_SIZE = 5,
  CACHE_ROW_SIZE = 10
};

typedef struct
{
  int address;
  int data[CACHE_ROW_SIZE];
  int last_access;
} cpu_cache;

extern uint16_t accumulator;
extern uint16_t command_counter;
extern int16_t random_access_memory[RAM_SIZE];
extern uint8_t flag_register;
extern uint8_t idle_clock_counter;
extern uint32_t selected_cell;
extern cpu_cache l1_cache[CACHE_SIZE];
extern bool update_l1_cache;

int sc_memoryInit (void);
int sc_memoryGet (int address, int *value);
int sc_memorySet (int address, int value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);

int sc_regInit (void);
int sc_regGet (enum flags reg, int *value);
int sc_regSet (enum flags reg, int value);

int sc_accumulatorInit (void);
int sc_accumulatorGet (int *value);
int sc_accumulatorSet (int value);

int sc_icounterInit (void);
int sc_icounterGet (int *value);
int sc_icounterSet (int value);

int sc_commandValidate (int command);
int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);

void sc_cacheInit (void);
void sc_cacheUpdate (int address, int *value);

void sc_reset (void);

#endif /* MY_SIMPLE_COMPUTER_H */
