#include "../include/mySimpleComputer.h"

uint16_t accumulator;
uint16_t command_counter;
int16_t random_access_memory[RAM_SIZE];
uint8_t flag_register;
uint8_t idle_clock_counter;
uint32_t selected_cell = 0;