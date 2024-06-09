#ifndef CONSOLE_H
#define CONSOLE_H

#include "../include/myReadKey.h"
#include "../include/myTerm.h"

void printAccumulator (void);
void printCell (int address, enum colors fg, enum colors bg);
void printCommand (void);
void printCounters (void);
void printDecodedCommand (int value);
void printFlags (void);
void printTerm (void);
void printKeys (void);
void printBigCell (void);

void printTui (void);
void processInput (enum keys key, int *exit_flag);

#endif /* CONSOLE_H */
