#include "../include/myBigChars.h"

#include <stdio.h>

#include "../include/myTerm.h"

int
bc_box (int x1, int y1, int x2, int y2, enum colors box_fg, enum colors box_bg,
        const char *header, enum colors header_fg, enum colors header_bg)
{
  const int terminal_offset = 1;

  mt_setBgColor (box_bg);
  mt_setFgColor (box_fg);

  for (int i = x1 + terminal_offset; i < x2; ++i)
    {
      mt_gotoXY (i, y1);
      bc_printA (FRAME_HORISONTAL_LINE);

      mt_gotoXY (i, y2);
      bc_printA (FRAME_HORISONTAL_LINE);
    }

  for (int i = y1 + terminal_offset; i < y2; ++i)
    {
      mt_gotoXY (x1, i);
      bc_printA (FRAME_VERTICAL_LINE);

      mt_gotoXY (x2, i);
      bc_printA (FRAME_VERTICAL_LINE);
    }

  mt_gotoXY (x1, y1);
  bc_printA (FRAME_TL_CORNER);

  mt_gotoXY (x2, y1);
  bc_printA (FRAME_TR_CORNER);

  mt_gotoXY (x1, y2);
  bc_printA (FRAME_BL_CORNER);

  mt_gotoXY (x2, y2);
  bc_printA (FRAME_BR_CORNER);

  mt_setBgColor (header_bg);
  mt_setFgColor (header_fg);

  mt_gotoXY ((x1 + x2) / 2 - bc_strlen (header) / 2.0, y1);

  printf (" %s ", header);

  mt_setDefaultColor ();

  return 0;
}
