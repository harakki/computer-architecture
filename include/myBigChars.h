#ifndef MY_BIG_CHARS_H
#define MY_BIG_CHARS_H

#include <stddef.h>
#include <stdint.h>

#include "myTerm.h"

enum big_char_sizes
{
  BIG_CHAR_SIZE = 4,
  BIG_CHAR_HEIGHT = 8,
  BIG_CHAR_WIDTH = 8
};

enum frame_elements
{
  FRAME_TL_CORNER = 'l',
  FRAME_TR_CORNER = 'k',
  FRAME_BL_CORNER = 'm',
  FRAME_BR_CORNER = 'j',
  FRAME_HORISONTAL_LINE = 'q',
  FRAME_VERTICAL_LINE = 'x',
  FRAME_BLACK_BOX = 'a'
};

extern int32_t char_patterns[18][2];

size_t bc_strlen (const char *str);
int bc_getBigCharPosition (int *big, int x, int y, int *value);
int bc_setBigCharPosition (int *big, int x, int y, int value);
int bc_readBigChar (int fd, int *big, int need_count, int *count);
int bc_writeBigChar (int fd, int *font_bitmap, int symbols_amount);
int bc_box (int x1, int y1, int x2, int y2, enum colors box_fg,
            enum colors box_bg, const char *header, enum colors header_fg,
            enum colors header_bg);
int bc_printA (const char str);
int bc_printBigChar (int *big, int x, int y, enum colors bg, enum colors fg);

#endif /* MY_BIG_CHARS_H */
