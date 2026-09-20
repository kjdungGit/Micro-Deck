/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --no-compress --stride 1 --align 1 --font slacksideOne-Regular.ttf --range 0-127 --format lvgl -o SlacksideOne20.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef SLACKSIDEONE20
#define SLACKSIDEONE20 1
#endif

#if SLACKSIDEONE20

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+000D "\r" */
    0x0,

    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x2d, 0xb6, 0xda, 0x18,

    /* U+0022 "\"" */
    0x96, 0xe4,

    /* U+0023 "#" */
    0x12, 0xb, 0xf, 0xcf, 0xe3, 0x61, 0xb3, 0xfe,
    0xf8, 0x6c, 0x34, 0x2, 0x0,

    /* U+0024 "$" */
    0x0, 0x18, 0xf3, 0xf4, 0xab, 0xe, 0xe, 0x16,
    0x2e, 0xfb, 0xe2, 0x0, 0x0,

    /* U+0025 "%" */
    0x1, 0x1c, 0xcd, 0x62, 0xd8, 0x6c, 0x3, 0x20,
    0x9c, 0x6b, 0x33, 0xcc, 0x0,

    /* U+0026 "&" */
    0x78, 0xf9, 0xb3, 0xc7, 0x8e, 0x3f, 0xee, 0xfd,
    0xec,

    /* U+0027 "'" */
    0x3f,

    /* U+0028 "(" */
    0x36, 0xcc, 0xcc, 0xcc, 0xc7,

    /* U+0029 ")" */
    0x47, 0x33, 0x33, 0x36, 0xec,

    /* U+002A "*" */
    0x31, 0xfd, 0xe7, 0xe3, 0x4, 0x0,

    /* U+002B "+" */
    0x10, 0xcf, 0xfe, 0x30, 0x80,

    /* U+002C "," */
    0xc8, 0x0,

    /* U+002D "-" */
    0xfe,

    /* U+002E "." */
    0xc8,

    /* U+002F "/" */
    0x0, 0x3, 0x6, 0x4, 0xc, 0x18, 0x10, 0x30,
    0x60, 0x40, 0xc0,

    /* U+0030 "0" */
    0x18, 0x19, 0x98, 0x6c, 0x3c, 0x1e, 0xf, 0x5,
    0x86, 0x46, 0x1e, 0x0,

    /* U+0031 "1" */
    0x77, 0x37, 0x66, 0x6c, 0xcc, 0x0,

    /* U+0032 "2" */
    0x3e, 0x33, 0x3, 0x7, 0xe, 0xc, 0x18, 0x38,
    0xfc, 0xff,

    /* U+0033 "3" */
    0x18, 0x3c, 0x18, 0x71, 0xc3, 0x83, 0x6, 0x1c,
    0xf1, 0xc0,

    /* U+0034 "4" */
    0xc, 0x1c, 0x38, 0x34, 0x6c, 0xcc, 0xff, 0x7c,
    0x18, 0x18, 0x8,

    /* U+0035 "5" */
    0x41, 0x7d, 0xf0, 0xc3, 0x8f, 0x6, 0x18, 0x67,
    0x0,

    /* U+0036 "6" */
    0x0, 0x31, 0x8c, 0x61, 0x8d, 0xb3, 0xcd, 0xf7,
    0x80,

    /* U+0037 "7" */
    0x5f, 0x8f, 0x1c, 0x30, 0xc1, 0x83, 0xc, 0x18,
    0x30,

    /* U+0038 "8" */
    0x78, 0xc9, 0x3, 0xc3, 0x6, 0x1c, 0x64, 0xd9,
    0xe0,

    /* U+0039 "9" */
    0x30, 0xf3, 0x36, 0x27, 0xc1, 0x86, 0xc, 0x30,
    0x60, 0x80,

    /* U+003A ":" */
    0xd, 0xc, 0x80,

    /* U+003B ";" */
    0xd0, 0x70,

    /* U+003C "<" */
    0x19, 0x9d, 0xc4, 0x38, 0x40,

    /* U+003D "=" */
    0xf8, 0x4, 0xf0,

    /* U+003E ">" */
    0x61, 0x4, 0x37, 0x73, 0x0,

    /* U+003F "?" */
    0x38, 0xdf, 0x18, 0x30, 0xc3, 0x6, 0x8, 0x0,
    0x40, 0x40,

    /* U+0040 "@" */
    0x1f, 0x83, 0xe, 0x60, 0x24, 0x1, 0xdf, 0x99,
    0xd9, 0x99, 0x99, 0xfb, 0xdc, 0xe6, 0x0, 0x1f,
    0x80,

    /* U+0041 "A" */
    0x3, 0xc0, 0xf8, 0x33, 0x8c, 0x73, 0x8e, 0x61,
    0xd9, 0xb3, 0x6, 0x40, 0xd0, 0x10,

    /* U+0042 "B" */
    0xc, 0x19, 0x8c, 0xc4, 0x66, 0x73, 0x31, 0x88,
    0xcc, 0x46, 0x66, 0x16, 0x0,

    /* U+0043 "C" */
    0x6, 0xf, 0xce, 0xe, 0x6, 0x6, 0x3, 0x1,
    0x80, 0x40, 0x3f, 0x6, 0x0,

    /* U+0044 "D" */
    0xe, 0x11, 0x88, 0x6c, 0x36, 0x1a, 0xd, 0xd,
    0x8e, 0xce, 0x6c, 0x0,

    /* U+0045 "E" */
    0x6, 0x1f, 0x40, 0x60, 0x40, 0x58, 0xc0, 0xc0,
    0xc0, 0xf8,

    /* U+0046 "F" */
    0x1f, 0x8f, 0x18, 0xc, 0x6, 0x46, 0x73, 0x1,
    0x80, 0xc0, 0x60, 0x0,

    /* U+0047 "G" */
    0x1e, 0x3e, 0x70, 0x60, 0xe0, 0xc7, 0xc2, 0xc6,
    0x6c, 0x78,

    /* U+0048 "H" */
    0x0, 0x23, 0x2, 0x30, 0x63, 0x6, 0x70, 0x66,
    0xf6, 0x64, 0xc6, 0xc, 0xc0, 0xcc, 0xc, 0x40,
    0x80,

    /* U+0049 "I" */
    0x6d, 0xb7, 0xb6, 0xd0,

    /* U+004A "J" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x6, 0xe,
    0x7c, 0x78,

    /* U+004B "K" */
    0x20, 0x98, 0xdc, 0xec, 0xe6, 0xe3, 0x63, 0x11,
    0x8c, 0xc6, 0x61, 0x0,

    /* U+004C "L" */
    0x10, 0x38, 0x30, 0x30, 0x60, 0x60, 0x60, 0xe0,
    0xfe, 0x7e,

    /* U+004D "M" */
    0x1e, 0x18, 0x79, 0xf3, 0x36, 0xcc, 0xf3, 0x63,
    0xcd, 0x86, 0x36, 0x0, 0xf0, 0x2, 0xc0, 0x1b,
    0x0, 0x60, 0x0, 0x80,

    /* U+004E "N" */
    0x30, 0x19, 0xc0, 0xdf, 0xc, 0xd8, 0x66, 0x63,
    0x33, 0x31, 0x8d, 0x98, 0x6c, 0xc1, 0xe6, 0xe,
    0x0, 0x0,

    /* U+004F "O" */
    0x19, 0xe, 0x67, 0xd, 0x83, 0xc0, 0xf0, 0x3c,
    0x1b, 0xe, 0x7f, 0xf, 0x0,

    /* U+0050 "P" */
    0xf, 0x11, 0xdc, 0x6c, 0x36, 0x37, 0x7b, 0x31,
    0x80, 0xc0, 0x40, 0x0, 0x0,

    /* U+0051 "Q" */
    0x3e, 0x39, 0x98, 0x78, 0x3c, 0x1e, 0xf, 0x37,
    0x8e, 0xc7, 0x3e, 0xc4, 0x0,

    /* U+0052 "R" */
    0x16, 0x19, 0x8c, 0x4e, 0x66, 0x73, 0x31, 0x99,
    0x8c, 0xc2, 0x61, 0x0,

    /* U+0053 "S" */
    0x3c, 0xfd, 0x83, 0x3, 0x3, 0x3, 0x6, 0xbc,
    0xf0,

    /* U+0054 "T" */
    0xff, 0x10, 0x8, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x30, 0x10,

    /* U+0055 "U" */
    0x0, 0x30, 0xb8, 0x5c, 0x6c, 0x36, 0x1b, 0x19,
    0x8c, 0xce, 0x3e, 0xe, 0x0,

    /* U+0056 "V" */
    0xc0, 0x1c, 0xb, 0x83, 0x70, 0xee, 0x19, 0xc7,
    0x38, 0xc3, 0x30, 0x6e, 0x7, 0x0, 0x0, 0x0,

    /* U+0057 "W" */
    0xc0, 0x3, 0xc, 0x3c, 0x30, 0xf1, 0xc6, 0xcf,
    0x3b, 0x3c, 0xcd, 0x96, 0x3e, 0x78, 0x71, 0xc1,
    0x82, 0x0,

    /* U+0058 "X" */
    0x61, 0x11, 0xcd, 0xc3, 0xc1, 0xc0, 0xe0, 0xf0,
    0xcc, 0xe6, 0x61, 0x0,

    /* U+0059 "Y" */
    0x1, 0x61, 0x91, 0xcd, 0xc3, 0xc0, 0x40, 0x20,
    0x30, 0x18, 0xc, 0x4, 0x0,

    /* U+005A "Z" */
    0xfe, 0x7f, 0x7, 0x6, 0xc, 0x18, 0x38, 0x70,
    0xfe, 0xff,

    /* U+005B "[" */
    0x77, 0x66, 0xcc, 0xcc, 0xc7,

    /* U+005C "\\" */
    0xc0, 0xc0, 0x81, 0x83, 0x3, 0x6, 0x6, 0x4,
    0xc,

    /* U+005D "]" */
    0xc7, 0x33, 0x37, 0x66, 0x6e, 0xc0,

    /* U+005E "^" */
    0x1c, 0x1b, 0x18, 0xd8, 0x30,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0xc8,

    /* U+0061 "a" */
    0x0, 0x7c, 0x60, 0xc0, 0xcc, 0xde, 0x70,

    /* U+0062 "b" */
    0x20, 0x20, 0x60, 0x60, 0x60, 0x5c, 0xc2, 0xc6,
    0xc6, 0xdc, 0x80,

    /* U+0063 "c" */
    0x39, 0xfc, 0x30, 0xc9, 0xe0,

    /* U+0064 "d" */
    0x1, 0x0, 0xc0, 0x40, 0x60, 0x31, 0x9b, 0xed,
    0x84, 0xc6, 0x3b, 0x0,

    /* U+0065 "e" */
    0x3b, 0x9f, 0xa0, 0xfc, 0xe0,

    /* U+0066 "f" */
    0x1c, 0x63, 0xc, 0xfd, 0xc6, 0x18, 0x61, 0x80,

    /* U+0067 "g" */
    0x3c, 0x76, 0x46, 0x6e, 0x3e, 0x6, 0x6, 0x8c,
    0x78,

    /* U+0068 "h" */
    0x30, 0x60, 0xc3, 0x7, 0xce, 0xd9, 0xe3, 0xc7,
    0x88,

    /* U+0069 "i" */
    0x6d, 0x25, 0xb6,

    /* U+006A "j" */
    0xc, 0x30, 0x3, 0xc, 0x30, 0x86, 0x18, 0x63,
    0x3c,

    /* U+006B "k" */
    0x20, 0x41, 0x83, 0x6, 0x4d, 0x96, 0x2c, 0xd9,
    0xb0,

    /* U+006C "l" */
    0x3, 0x26, 0x66, 0x64, 0xcc, 0xc0,

    /* U+006D "m" */
    0x60, 0x7, 0xde, 0x7f, 0x66, 0x63, 0xc6, 0x3c,
    0x62,

    /* U+006E "n" */
    0xde, 0xf7, 0xc3, 0xc3, 0x83,

    /* U+006F "o" */
    0x71, 0x82, 0x1c, 0x3f, 0xce, 0x0,

    /* U+0070 "p" */
    0x26, 0x1b, 0x8c, 0x6c, 0x36, 0xf3, 0x63, 0x1,
    0x80, 0xc0, 0x20, 0x0,

    /* U+0071 "q" */
    0x71, 0xee, 0x1c, 0x2e, 0x4d, 0x83, 0x4, 0x8,
    0x10,

    /* U+0072 "r" */
    0x41, 0x7f, 0xb8, 0xc2, 0x0,

    /* U+0073 "s" */
    0x39, 0x7, 0x83, 0x8d, 0xe0,

    /* U+0074 "t" */
    0x10, 0xcf, 0xcc, 0x20, 0x86, 0x18, 0x41, 0x0,

    /* U+0075 "u" */
    0x0, 0xc2, 0xc6, 0xce, 0x7f, 0x78,

    /* U+0076 "v" */
    0xc0, 0xd8, 0x66, 0x30, 0x98, 0x3c, 0x6, 0x0,

    /* U+0077 "w" */
    0x80, 0xc, 0x73, 0x4f, 0x66, 0x9e, 0x79, 0xc3,
    0x18,

    /* U+0078 "x" */
    0x84, 0xd8, 0xe1, 0xce, 0xd8, 0x40,

    /* U+0079 "y" */
    0x41, 0x91, 0xcd, 0xc3, 0xc1, 0xc1, 0xc0, 0xc0,
    0xc0, 0xc0, 0x0,

    /* U+007A "z" */
    0xfc, 0xf1, 0x8c, 0x79, 0xf0,

    /* U+007B "{" */
    0x1c, 0x43, 0xc, 0x61, 0x82, 0x8, 0x20, 0xe0,

    /* U+007C "|" */
    0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0x1, 0xc3, 0xc, 0x30, 0xf3, 0xc, 0x61, 0x8c,
    0x0,

    /* U+007E "~" */
    0x18, 0x1e, 0x7e, 0x71, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 200, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 85, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 112, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 8, .adv_w = 177, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 21, .adv_w = 150, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 34, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 146, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 67, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 57, .adv_w = 106, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 104, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 156, .box_w = 7, .box_h = 6, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 73, .adv_w = 142, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 78, .adv_w = 74, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 80, .adv_w = 140, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 81, .adv_w = 78, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 156, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 177, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 136, .box_w = 4, .box_h = 11, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 111, .adv_w = 177, .box_w = 8, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 150, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 168, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 142, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 136, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 151, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 143, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 141, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 191, .adv_w = 78, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 193, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 198, .adv_w = 113, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 201, .adv_w = 116, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 206, .adv_w = 147, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 216, .adv_w = 240, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 233, .adv_w = 205, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 168, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 260, .adv_w = 177, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 183, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 177, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 168, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 219, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 103, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 162, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 193, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 155, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 275, .box_w = 14, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 390, .adv_w = 255, .box_w = 13, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 408, .adv_w = 201, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 190, .box_w = 9, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 434, .adv_w = 182, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 447, .adv_w = 177, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 168, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 175, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 202, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 507, .adv_w = 266, .box_w = 14, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 172, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 169, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 104, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 106, .box_w = 4, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 177, .box_w = 9, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 585, .adv_w = 142, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 77, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 587, .adv_w = 155, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 163, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 605, .adv_w = 125, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 175, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 135, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 153, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 644, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 87, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 665, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 91, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 680, .adv_w = 219, .box_w = 12, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 689, .adv_w = 164, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 140, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 176, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 712, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 721, .adv_w = 139, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 127, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 148, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 739, .adv_w = 161, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 191, .box_w = 10, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 227, .box_w = 12, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 150, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 176, .box_w = 9, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 779, .adv_w = 138, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 73, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 795, .adv_w = 138, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 804, .adv_w = 192, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 3}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 13, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 2,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    9, 35,
    15, 76,
    16, 76,
    17, 17,
    18, 19,
    18, 20,
    19, 20,
    19, 21,
    19, 24,
    19, 73,
    19, 76,
    20, 21,
    21, 19,
    21, 21,
    22, 19,
    22, 20,
    22, 21,
    22, 27,
    22, 35,
    23, 19,
    23, 20,
    23, 24,
    24, 20,
    25, 20,
    25, 35,
    26, 19,
    26, 20,
    26, 21,
    27, 19,
    27, 20,
    27, 21,
    35, 71,
    35, 73,
    35, 76,
    35, 91,
    36, 14,
    36, 16,
    36, 35,
    36, 44,
    36, 76,
    37, 14,
    37, 15,
    37, 16,
    37, 35,
    37, 38,
    37, 42,
    37, 44,
    37, 45,
    37, 51,
    37, 58,
    37, 67,
    37, 69,
    37, 74,
    37, 76,
    37, 80,
    37, 81,
    37, 84,
    38, 14,
    38, 16,
    38, 35,
    38, 44,
    38, 52,
    38, 65,
    38, 71,
    38, 76,
    39, 14,
    39, 35,
    39, 44,
    39, 47,
    39, 48,
    39, 50,
    39, 76,
    40, 14,
    40, 15,
    40, 22,
    40, 35,
    40, 41,
    40, 44,
    40, 48,
    40, 49,
    40, 51,
    40, 52,
    40, 65,
    40, 67,
    40, 69,
    40, 70,
    40, 71,
    40, 76,
    40, 79,
    40, 80,
    40, 81,
    40, 82,
    40, 83,
    40, 84,
    40, 85,
    40, 88,
    40, 89,
    40, 90,
    40, 91,
    40, 92,
    41, 44,
    41, 76,
    42, 35,
    42, 44,
    42, 65,
    42, 67,
    42, 71,
    42, 76,
    43, 35,
    43, 48,
    43, 65,
    43, 73,
    43, 76,
    44, 16,
    44, 35,
    44, 47,
    44, 65,
    44, 67,
    44, 69,
    44, 70,
    44, 71,
    44, 73,
    44, 76,
    44, 82,
    44, 85,
    44, 91,
    45, 14,
    45, 15,
    45, 16,
    45, 35,
    45, 37,
    45, 41,
    45, 44,
    45, 46,
    45, 47,
    45, 51,
    45, 65,
    45, 67,
    45, 68,
    45, 69,
    45, 70,
    45, 71,
    45, 73,
    45, 74,
    45, 75,
    45, 76,
    45, 79,
    45, 80,
    45, 81,
    45, 82,
    45, 83,
    45, 84,
    45, 85,
    45, 86,
    45, 87,
    45, 88,
    45, 89,
    45, 90,
    45, 91,
    45, 92,
    46, 54,
    46, 59,
    46, 76,
    46, 86,
    46, 88,
    46, 89,
    46, 91,
    47, 35,
    47, 48,
    47, 76,
    47, 91,
    48, 14,
    48, 15,
    48, 16,
    48, 35,
    48, 36,
    48, 43,
    48, 44,
    48, 47,
    48, 49,
    48, 52,
    48, 53,
    48, 58,
    48, 65,
    48, 67,
    48, 69,
    48, 70,
    48, 71,
    48, 73,
    48, 75,
    48, 76,
    48, 79,
    48, 80,
    48, 81,
    48, 82,
    48, 83,
    48, 84,
    48, 85,
    48, 87,
    48, 88,
    48, 89,
    48, 90,
    48, 91,
    48, 92,
    49, 16,
    49, 35,
    49, 44,
    49, 47,
    49, 48,
    49, 58,
    49, 59,
    49, 76,
    50, 14,
    50, 15,
    50, 16,
    50, 35,
    50, 44,
    50, 65,
    50, 67,
    50, 69,
    50, 70,
    50, 71,
    50, 73,
    50, 76,
    50, 78,
    50, 79,
    50, 80,
    50, 81,
    50, 83,
    50, 84,
    50, 85,
    50, 86,
    50, 87,
    50, 88,
    50, 89,
    50, 90,
    50, 91,
    50, 92,
    51, 35,
    51, 44,
    51, 59,
    51, 73,
    51, 76,
    51, 82,
    51, 91,
    52, 35,
    52, 44,
    52, 47,
    52, 53,
    52, 65,
    52, 76,
    53, 14,
    53, 35,
    53, 45,
    53, 47,
    53, 74,
    53, 76,
    54, 14,
    54, 15,
    54, 16,
    54, 22,
    54, 35,
    54, 37,
    54, 39,
    54, 42,
    54, 43,
    54, 44,
    54, 45,
    54, 46,
    54, 47,
    54, 48,
    54, 49,
    54, 51,
    54, 55,
    54, 65,
    54, 67,
    54, 68,
    54, 69,
    54, 70,
    54, 71,
    54, 73,
    54, 74,
    54, 75,
    54, 76,
    54, 77,
    54, 79,
    54, 80,
    54, 81,
    54, 82,
    54, 83,
    54, 84,
    54, 85,
    54, 86,
    54, 87,
    54, 88,
    54, 89,
    54, 90,
    54, 91,
    54, 92,
    55, 35,
    55, 44,
    55, 48,
    55, 76,
    56, 14,
    56, 15,
    56, 16,
    56, 22,
    56, 35,
    56, 37,
    56, 41,
    56, 43,
    56, 44,
    56, 45,
    56, 46,
    56, 47,
    56, 48,
    56, 51,
    56, 65,
    56, 67,
    56, 68,
    56, 69,
    56, 70,
    56, 71,
    56, 72,
    56, 73,
    56, 74,
    56, 76,
    56, 77,
    56, 79,
    56, 80,
    56, 81,
    56, 82,
    56, 83,
    56, 84,
    56, 85,
    56, 86,
    56, 88,
    56, 89,
    56, 90,
    56, 91,
    56, 92,
    57, 14,
    57, 15,
    57, 16,
    57, 35,
    57, 37,
    57, 44,
    57, 48,
    57, 49,
    57, 51,
    57, 58,
    57, 65,
    57, 67,
    57, 68,
    57, 69,
    57, 70,
    57, 71,
    57, 72,
    57, 73,
    57, 74,
    57, 76,
    57, 77,
    57, 79,
    57, 80,
    57, 81,
    57, 82,
    57, 83,
    57, 84,
    57, 85,
    57, 86,
    57, 88,
    57, 89,
    57, 90,
    57, 91,
    57, 92,
    58, 14,
    58, 22,
    58, 49,
    58, 65,
    58, 67,
    58, 68,
    58, 69,
    58, 70,
    58, 71,
    58, 72,
    58, 76,
    58, 81,
    58, 82,
    58, 83,
    58, 88,
    58, 89,
    58, 91,
    59, 14,
    59, 15,
    59, 16,
    59, 35,
    59, 44,
    59, 45,
    59, 46,
    59, 47,
    59, 48,
    59, 49,
    59, 50,
    59, 51,
    59, 52,
    59, 65,
    59, 67,
    59, 69,
    59, 70,
    59, 71,
    59, 72,
    59, 73,
    59, 74,
    59, 75,
    59, 76,
    59, 77,
    59, 79,
    59, 80,
    59, 81,
    59, 82,
    59, 83,
    59, 84,
    59, 85,
    59, 87,
    59, 88,
    59, 89,
    59, 90,
    59, 91,
    59, 92,
    60, 76,
    65, 76,
    67, 54,
    67, 73,
    67, 76,
    67, 82,
    67, 86,
    67, 91,
    68, 54,
    68, 76,
    68, 91,
    69, 76,
    69, 86,
    70, 14,
    70, 71,
    70, 76,
    70, 78,
    71, 73,
    71, 76,
    71, 82,
    71, 86,
    72, 35,
    72, 44,
    72, 67,
    72, 71,
    72, 72,
    72, 73,
    72, 76,
    73, 76,
    73, 86,
    74, 54,
    74, 59,
    74, 76,
    75, 70,
    75, 73,
    75, 76,
    75, 79,
    75, 81,
    75, 82,
    76, 76,
    77, 44,
    77, 59,
    77, 65,
    77, 73,
    77, 76,
    77, 82,
    77, 85,
    77, 88,
    78, 44,
    78, 65,
    78, 70,
    78, 71,
    78, 73,
    78, 76,
    78, 77,
    78, 78,
    78, 82,
    78, 85,
    78, 91,
    79, 76,
    79, 82,
    79, 91,
    80, 73,
    80, 76,
    80, 86,
    80, 91,
    81, 76,
    81, 82,
    82, 73,
    82, 76,
    82, 82,
    83, 76,
    84, 14,
    84, 65,
    84, 73,
    84, 76,
    84, 79,
    84, 91,
    85, 76,
    85, 86,
    86, 16,
    86, 35,
    86, 44,
    86, 65,
    86, 67,
    86, 71,
    86, 73,
    86, 74,
    86, 75,
    86, 76,
    86, 77,
    86, 79,
    86, 80,
    86, 81,
    86, 82,
    86, 84,
    86, 85,
    86, 86,
    86, 91,
    87, 73,
    87, 76,
    87, 82,
    88, 14,
    88, 35,
    88, 73,
    88, 76,
    89, 35,
    89, 67,
    89, 71,
    89, 73,
    89, 74,
    89, 76,
    89, 85,
    90, 73,
    90, 76,
    91, 14,
    91, 16,
    91, 35,
    91, 65,
    91, 73,
    91, 76,
    91, 85,
    92, 76
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -26, -26, -19, -48, -16, -16, -16, -22,
    -16, -16, -32, -10, -16, -16, -16, -22,
    -16, -13, -16, -16, -16, -16, -16, -16,
    -16, -16, -16, -16, -16, -16, -16, -10,
    -13, -32, -16, -16, -16, -19, -16, -38,
    -26, -16, -16, -26, -10, -6, -16, -10,
    -13, -13, -19, -16, -16, -38, -16, -13,
    -13, -26, -26, -19, -16, -10, -16, -10,
    -38, -26, -32, -26, -19, -10, -13, -38,
    -26, -16, -16, -32, -10, -32, -19, -10,
    -10, -16, -32, -26, -26, -26, -22, -48,
    -26, -19, -16, -32, -32, -26, -26, -26,
    -16, -16, -22, -16, -16, -38, -19, -13,
    -16, -13, -10, -38, -19, -10, -16, -16,
    -38, -19, -16, -13, -16, -13, -13, -13,
    -13, -16, -38, -16, -13, -16, -26, -26,
    -26, -22, -10, -10, -22, -10, -16, -10,
    -26, -22, -13, -22, -16, -19, -29, -13,
    -13, -48, -13, -16, -22, -32, -19, -19,
    -26, -16, -16, -13, -13, -13, -26, -16,
    -16, -16, -38, -26, -16, -10, -26, -10,
    -6, -38, -13, -26, -16, -19, -22, -10,
    -13, -10, -26, -6, -6, -13, -10, -26,
    -16, -16, -16, -16, -26, -10, -42, -10,
    -13, -16, -19, -10, -13, -26, -16, -16,
    -16, -16, -16, -16, -19, -16, -16, -13,
    -10, -10, -10, -38, -26, -16, -32, -26,
    -32, -32, -26, -26, -26, -26, -26, -38,
    -16, -26, -16, -26, -26, -19, -26, -10,
    -10, -10, -10, -10, -19, -16, -10, -10,
    -10, -16, -32, -16, -16, -16, -16, -13,
    -10, -16, -38, -16, -16, -10, -13, -13,
    -38, -26, -26, -26, -16, -38, -13, -13,
    -10, -10, -32, -16, -16, -32, -16, -16,
    -10, -10, -32, -32, -10, -32, -26, -32,
    -45, -26, -16, -48, -13, -26, -26, -32,
    -38, -32, -26, -38, -16, -22, -16, -26,
    -26, -32, -26, -26, -16, -10, -42, -16,
    -19, -26, -16, -32, -10, -10, -10, -32,
    -13, -10, -19, -10, -10, -32, -26, -16,
    -26, -26, -26, -16, -32, -26, -42, -13,
    -26, -16, -26, -32, -26, -26, -26, -16,
    -13, -16, -16, -26, -19, -16, -19, -26,
    -32, -10, -26, -6, -10, -10, -13, -32,
    -32, -13, -32, -32, -32, -13, -32, -13,
    -48, -10, -26, -26, -26, -32, -32, -32,
    -32, -13, -13, -13, -26, -26, -22, -16,
    -16, -13, -16, -22, -13, -22, -22, -26,
    -26, -42, -26, -16, -26, -26, -26, -26,
    -16, -26, -26, -32, -26, -13, -16, -26,
    -10, -16, -13, -13, -16, -32, -32, -26,
    -26, -26, -16, -32, -13, -16, -42, -13,
    -26, -16, -26, -32, -26, -26, -32, -26,
    -16, -26, -16, -26, -26, -35, -32, -13,
    -13, -32, -13, -13, -16, -16, -32, -13,
    -32, -10, -16, -10, -38, -13, -13, -38,
    -10, -13, -16, -26, -10, -13, -10, -16,
    -32, -32, -13, -10, -13, -32, -16, -16,
    -38, -10, -10, -16, -32, -16, -13, -19,
    -16, -35, -10, -16, -6, -16, -19, -13,
    -10, -16, -38, -10, -19, -19, -16, -13,
    -32, -13, -13, -16, -32, -13, -16, -32,
    -10, -13, -32, -13, -32, -16, -26, -13,
    -32, -10, -13, -32, -10, -16, -26, -16,
    -26, -13, -26, -26, -13, -10, -42, -13,
    -13, -10, -13, -26, -13, -13, -13, -16,
    -13, -32, -10, -16, -16, -10, -32, -16,
    -10, -10, -13, -10, -32, -13, -13, -32,
    -16, -16, -16, -26, -13, -32, -10, -32
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 552,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 2,
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
const lv_font_t slacksideOne20 = {
#else
lv_font_t slacksideOne20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if SLACKSIDEONE20*/
