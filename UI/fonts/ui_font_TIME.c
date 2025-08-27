/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font /home/skyforever/SquareLine/assets/051-上首酷方体.ttf -o /home/skyforever/SquareLine/assets/ui_font_TIME.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_TIME
#define UI_FONT_TIME 1
#endif

#if UI_FONT_TIME

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xff, 0xe3, 0xf0,

    /* U+0022 "\"" */
    0xff, 0xf0,

    /* U+0023 "#" */
    0x33, 0x8c, 0xef, 0xff, 0xff, 0x73, 0x1c, 0xcf,
    0xff, 0xff, 0x67, 0x19, 0xc0,

    /* U+0024 "$" */
    0xff, 0xff, 0xfe, 0xff, 0xb8, 0xff, 0xff, 0xf0,
    0xef, 0xbb, 0xff, 0xff, 0xf0, 0xe0,

    /* U+0025 "%" */
    0xf1, 0x9e, 0x73, 0xcc, 0x7b, 0x8f, 0x60, 0x1c,
    0x3, 0x78, 0xcf, 0x19, 0xe6, 0x3c,

    /* U+0026 "&" */
    0xff, 0x8f, 0xf8, 0xe3, 0x8f, 0x78, 0x3c, 0xef,
    0xfc, 0xe3, 0xee, 0x1f, 0xff, 0xdf, 0xf8,

    /* U+0027 "'" */
    0xfc,

    /* U+0028 "(" */
    0x3b, 0x9d, 0xce, 0x73, 0x9c, 0xe7, 0x1c, 0xe3,
    0x80,

    /* U+0029 ")" */
    0xe3, 0x9c, 0x73, 0x9c, 0xe7, 0x39, 0xdc, 0xee,
    0x0,

    /* U+002A "*" */
    0x32, 0xdf, 0xde, 0x79, 0x20,

    /* U+002B "+" */
    0x1c, 0xe, 0x7, 0x1f, 0xff, 0xf8, 0xe0, 0x70,
    0x38, 0x1c, 0x0,

    /* U+002C "," */
    0x66, 0xe0,

    /* U+002D "-" */
    0xff, 0xff, 0xc0,

    /* U+002E "." */
    0xff, 0x80,

    /* U+002F "/" */
    0x3, 0x80, 0xe0, 0x70, 0x18, 0xe, 0x7, 0x1,
    0xc0, 0xe0, 0x30, 0x1c, 0xe, 0x0,

    /* U+0030 "0" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0031 "1" */
    0x7c, 0x1f, 0x1, 0xc0, 0x70, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0xff, 0xff, 0xf0,

    /* U+0032 "2" */
    0xff, 0xff, 0xf0, 0x1c, 0x7, 0xff, 0xff, 0xfe,
    0x3, 0x80, 0xff, 0xff, 0xf0,

    /* U+0033 "3" */
    0xff, 0xff, 0xfc, 0x3, 0x80, 0x7f, 0xff, 0xff,
    0xc0, 0x38, 0x7, 0xff, 0xff, 0xfc,

    /* U+0034 "4" */
    0xe3, 0x9c, 0x73, 0x8e, 0x71, 0xce, 0x39, 0xc7,
    0x3f, 0xff, 0xff, 0x3, 0x80, 0x70,

    /* U+0035 "5" */
    0xff, 0xff, 0xfe, 0x3, 0x80, 0xff, 0xff, 0xf0,
    0x1c, 0x7, 0xff, 0xff, 0xf0,

    /* U+0036 "6" */
    0xff, 0xff, 0xfe, 0x3, 0x80, 0xff, 0xff, 0xfe,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0037 "7" */
    0xff, 0xff, 0xf0, 0x3c, 0xe, 0x3, 0x81, 0xe0,
    0x70, 0x1c, 0xe, 0x3, 0x80,

    /* U+0038 "8" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xff, 0xff, 0xfe,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0039 "9" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xff, 0xff, 0xf0,
    0x1c, 0x7, 0xff, 0xff, 0xf0,

    /* U+003A ":" */
    0xfc, 0x1, 0xf8,

    /* U+003B ";" */
    0x77, 0x0, 0x7, 0xe0,

    /* U+003C "<" */
    0x1, 0xc3, 0xf7, 0xf3, 0xe0, 0xf0, 0x3f, 0x83,
    0xfc, 0x1f, 0x0, 0xc0,

    /* U+003D "=" */
    0xff, 0xff, 0xc0, 0x0, 0xf, 0xff, 0xfc,

    /* U+003E ">" */
    0xe0, 0x3f, 0x7, 0xf8, 0x3f, 0x3, 0xc7, 0xff,
    0xe3, 0xc0, 0x80, 0x0,

    /* U+003F "?" */
    0xff, 0xff, 0xfe, 0x1c, 0xf, 0xf, 0x87, 0xc1,
    0xc0, 0x70, 0x1c, 0x0, 0x1, 0xc0, 0x70,

    /* U+0040 "@" */
    0xff, 0xff, 0xff, 0xfb, 0xff, 0x7f, 0xaf, 0xf5,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,

    /* U+0041 "A" */
    0xf, 0x0, 0xf0, 0x1f, 0x81, 0x98, 0x39, 0xc3,
    0xfc, 0x3e, 0xe7, 0xe, 0xe0, 0x7e, 0x7,

    /* U+0042 "B" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xff, 0xff, 0xfe,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0043 "C" */
    0xff, 0xff, 0xfe, 0x1f, 0x80, 0xe0, 0x38, 0xe,
    0x3, 0x87, 0xff, 0xff, 0xf0,

    /* U+0044 "D" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0045 "E" */
    0xff, 0xff, 0xfe, 0x3, 0x80, 0xff, 0xff, 0xfe,
    0x3, 0x80, 0xff, 0xff, 0xf0,

    /* U+0046 "F" */
    0xff, 0xff, 0xfe, 0x3, 0x80, 0xff, 0xff, 0xfe,
    0x3, 0x80, 0xe0, 0x38, 0x0,

    /* U+0047 "G" */
    0xff, 0xff, 0xfe, 0x1f, 0x80, 0xe7, 0xf9, 0xfe,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0048 "H" */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xff, 0xff, 0xfe,
    0x1f, 0x87, 0xe1, 0xf8, 0x70,

    /* U+0049 "I" */
    0xff, 0xff, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    0xff, 0xff,

    /* U+004A "J" */
    0x3, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1f, 0x8f,
    0xc7, 0xff, 0xff, 0xc0,

    /* U+004B "K" */
    0xe3, 0xb9, 0xce, 0xf3, 0xf8, 0xfc, 0x3f, 0xe,
    0xe3, 0x9c, 0xe3, 0xf8, 0xf0,

    /* U+004C "L" */
    0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0xff, 0xff, 0xc0,

    /* U+004D "M" */
    0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xef, 0x7e,
    0xf7, 0xef, 0x7e, 0xf7, 0xe6, 0x7e, 0x7,

    /* U+004E "N" */
    0xf1, 0xfe, 0x7f, 0x9f, 0xf7, 0xed, 0xfb, 0x7e,
    0x7f, 0x9f, 0xe7, 0xf8, 0xf0,

    /* U+004F "O" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0050 "P" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xff, 0xff, 0xfe,
    0x3, 0x80, 0xe0, 0x38, 0x0,

    /* U+0051 "Q" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0xb7, 0xff, 0xff, 0xf0, 0x60, 0x1f, 0x7,
    0xc0,

    /* U+0052 "R" */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xff, 0xff, 0xfe,
    0x3b, 0x8e, 0xe1, 0xf8, 0x70,

    /* U+0053 "S" */
    0xff, 0xff, 0xfe, 0x1f, 0x80, 0xff, 0xff, 0xf0,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0054 "T" */
    0xff, 0xff, 0xf1, 0xc0, 0x70, 0x1c, 0x7, 0x1,
    0xc0, 0x70, 0x1c, 0x7, 0x0,

    /* U+0055 "U" */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8, 0x7e,
    0x1f, 0x87, 0xff, 0xff, 0xf0,

    /* U+0056 "V" */
    0xe1, 0xf8, 0x6e, 0x19, 0x8e, 0x73, 0x9c, 0xc3,
    0x70, 0xfc, 0x3f, 0xf, 0x80,

    /* U+0057 "W" */
    0xc0, 0x3c, 0x67, 0xce, 0x6e, 0xf6, 0x6f, 0x66,
    0xf6, 0x7b, 0x67, 0x9c, 0x79, 0xc3, 0x9c,

    /* U+0058 "X" */
    0xe1, 0xdc, 0xe3, 0xf0, 0x78, 0x1e, 0x7, 0x83,
    0xf0, 0xfc, 0xf3, 0xf8, 0x70,

    /* U+0059 "Y" */
    0xe0, 0xee, 0x38, 0xee, 0xf, 0x80, 0xe0, 0x1c,
    0x3, 0x80, 0x70, 0xe, 0x1, 0xc0,

    /* U+005A "Z" */
    0xff, 0xff, 0xf0, 0x3c, 0x1e, 0xe, 0x7, 0x3,
    0x81, 0xc0, 0xff, 0xff, 0xf0,

    /* U+005B "[" */
    0xff, 0xf9, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xcf,
    0xfc,

    /* U+005C "\\" */
    0xe0, 0x1c, 0x3, 0x0, 0xe0, 0x1c, 0x7, 0x0,
    0xe0, 0x1c, 0x7, 0x0, 0xe0, 0x38,

    /* U+005D "]" */
    0xff, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x7f,
    0xfc,

    /* U+005E "^" */
    0x3c, 0xf9, 0xfb, 0x30,

    /* U+005F "_" */
    0xff, 0xff, 0xfc,

    /* U+0060 "`" */
    0xe6, 0x67,

    /* U+0061 "a" */
    0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff,

    /* U+0062 "b" */
    0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xe7, 0xe7, 0xe7,
    0xff, 0xff,

    /* U+0063 "c" */
    0xff, 0xff, 0xe7, 0xe0, 0xe7, 0xff, 0xff,

    /* U+0064 "d" */
    0x7, 0x7, 0x7, 0xff, 0xff, 0xe7, 0xe7, 0xe7,
    0xff, 0xff,

    /* U+0065 "e" */
    0xff, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff,

    /* U+0066 "f" */
    0x3f, 0x3f, 0x38, 0xff, 0xff, 0x38, 0x38, 0x38,
    0x38, 0x38,

    /* U+0067 "g" */
    0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0x7,
    0xff, 0xff,

    /* U+0068 "h" */
    0xe0, 0xe0, 0xe0, 0xff, 0xff, 0xe7, 0xe7, 0xe7,
    0xe7, 0xe7,

    /* U+0069 "i" */
    0xfc, 0x7f, 0xff, 0xfc,

    /* U+006A "j" */
    0x39, 0xc0, 0x73, 0x9c, 0xe7, 0x39, 0xcf, 0xff,
    0x80,

    /* U+006B "k" */
    0xe0, 0x70, 0x38, 0x1c, 0xee, 0xe7, 0xe3, 0xf1,
    0xdc, 0xe7, 0xf1, 0xc0,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xdf, 0xef, 0xf3, 0x79, 0xbc, 0xde, 0x6f, 0x36,

    /* U+006E "n" */
    0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,

    /* U+006F "o" */
    0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xff,

    /* U+0070 "p" */
    0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe0,
    0xe0, 0xe0,

    /* U+0071 "q" */
    0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0x7,
    0x7, 0x7,

    /* U+0072 "r" */
    0xe7, 0xff, 0xe7, 0xe, 0x1c, 0x38, 0x0,

    /* U+0073 "s" */
    0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff,

    /* U+0074 "t" */
    0x38, 0x38, 0x38, 0xff, 0xff, 0x38, 0x38, 0x38,
    0x3e, 0x3e,

    /* U+0075 "u" */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff,

    /* U+0076 "v" */
    0xe7, 0xe7, 0x67, 0x76, 0x7e, 0x3e, 0x3c,

    /* U+0077 "w" */
    0xcc, 0xf7, 0x3d, 0xcf, 0x7e, 0x7f, 0x9d, 0xe7,
    0x78,

    /* U+0078 "x" */
    0xe7, 0x7e, 0x3c, 0x3c, 0x3c, 0xff, 0xe7,

    /* U+0079 "y" */
    0xe3, 0x66, 0x66, 0x7c, 0x3c, 0x38, 0x38, 0x30,
    0x70, 0x60,

    /* U+007A "z" */
    0xff, 0xff, 0xe, 0x3c, 0x70, 0xff, 0xff,

    /* U+007B "{" */
    0x3e, 0x7c, 0xe1, 0xc3, 0x87, 0x1c, 0x3c, 0x38,
    0x70, 0xe1, 0xc3, 0xe7, 0xc0,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff, 0xfe,

    /* U+007D "}" */
    0xf9, 0xf0, 0xe1, 0xc3, 0x87, 0x7, 0x1e, 0x38,
    0x70, 0xe1, 0xcf, 0x9f, 0x0,

    /* U+007E "~" */
    0xf8, 0x7f, 0xc7, 0xe0, 0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 160, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 125, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 6, .adv_w = 125, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 8, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 35, .adv_w = 203, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 203, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 125, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 65, .adv_w = 125, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 125, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 83, .adv_w = 125, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 88, .adv_w = 172, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 99, .adv_w = 125, .box_w = 4, .box_h = 3, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 101, .adv_w = 172, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 104, .adv_w = 125, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 106, .adv_w = 156, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 188, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 188, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 125, .box_w = 3, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 125, .box_w = 4, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 188, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 172, .box_w = 9, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 278, .adv_w = 188, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 188, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 305, .adv_w = 188, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 203, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 156, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 172, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 172, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 219, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 188, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 543, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 219, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 188, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 156, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 672, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 156, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 695, .adv_w = 125, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 699, .adv_w = 188, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 125, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 704, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 711, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 755, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 765, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 94, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 110, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 788, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 94, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 172, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 826, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 836, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 846, .adv_w = 156, .box_w = 7, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 156, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 870, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 877, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 188, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 900, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 910, .adv_w = 164, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 125, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 930, .adv_w = 125, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 935, .adv_w = 125, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 948, .adv_w = 156, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 8}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_TIME = {
#else
lv_font_t ui_font_TIME = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_TIME*/

