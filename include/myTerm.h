#ifndef MY_TERM_H
#define MY_TERM_H

#define HISTORY_SIZE 5

typedef struct cell_history_item
{
  int address;
  int input_type;
  int data;
} cell_history_item_t;

typedef struct circular_buf
{
  cell_history_item_t history[HISTORY_SIZE];
  int index;
} circular_buf_t;

enum colors
{
  DEFAULT = -1,
  BLACK = 0,
  RED = 1,
  GREEN = 2,
  YELLOW = 3,
  BLUE = 4,
  MAGENTA = 5,
  CYAN = 6,
  WHITE = 7,
  BRIGHT_BLACK = 8,
  BRIGHT_RED = 9,
  BRIGHT_GREEN = 10,
  BRIGHT_YELLOW = 11,
  BRIGHT_BLUE = 12,
  BRIGHT_MAGENTA = 13,
  BRIGHT_CYAN = 14,
  BRIGHT_WHITE = 15
};

extern circular_buf_t term_history;

void mt_calculatePosition (int address, int element_length,
                           int ammount_per_row, int top_padding,
                           int left_padding);
int mt_clrscr (void);
int mt_delLine (void);
int mt_setCursorVisibility (int value);

void mt_getScreenSize (int *rows, int *cols);
int mt_gotoXY (int x, int y);

int mt_setDefaultColor (void);
int mt_setBgColor (enum colors color);
int mt_setFgColor (enum colors color);

void mt_termDequeue (cell_history_item_t *history);
void mt_termEnqueue (int address, int input);
void mt_termInit ();

#endif /* MY_TERM_H_ */
