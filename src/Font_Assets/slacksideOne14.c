/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --bpp 1 --size 14 --no-compress --stride 1 --align 1 --font SlacksideOne-Regular.ttf --range 0-127 --format lvgl -o slacksideOne14.c
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



#ifndef SLACKSIDEONE14
#define SLACKSIDEONE14 1
#endif

#if SLACKSIDEONE14

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
    0xea, 0xa0,

    /* U+0022 "\"" */
    0xb4,

    /* U+0023 "#" */
    0x0, 0xaf, 0xd4, 0xfd, 0x45, 0x0,

    /* U+0024 "$" */
    0x13, 0xbb, 0xc3, 0x19, 0x4e, 0x40,

    /* U+0025 "%" */
    0x9, 0x93, 0x66, 0x83, 0x65, 0xd1, 0x0,

    /* U+0026 "&" */
    0x67, 0x9c, 0xcf, 0xfb, 0xe0,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x7a, 0x49, 0x10,

    /* U+0029 ")" */
    0x44, 0x96, 0xc0,

    /* U+002A "*" */
    0x2b, 0xbe, 0x40,

    /* U+002B "+" */
    0x2, 0xf2,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x8, 0xc4, 0x44, 0x62, 0x0,

    /* U+0030 "0" */
    0x29, 0x38, 0x61, 0x8e, 0x27, 0x0,

    /* U+0031 "1" */
    0x6d, 0xad, 0x80,

    /* U+0032 "2" */
    0x38, 0xb0, 0xc6, 0x31, 0x8f, 0xc0,

    /* U+0033 "3" */
    0x20, 0xc6, 0x61, 0x1b, 0x80,

    /* U+0034 "4" */
    0x33, 0x15, 0x2f, 0x90, 0x80,

    /* U+0035 "5" */
    0x43, 0xf1, 0xe, 0x18, 0xcc,

    /* U+0036 "6" */
    0x36, 0x4a, 0x99, 0x60,

    /* U+0037 "7" */
    0x74, 0xe4, 0x23, 0x10, 0x80,

    /* U+0038 "8" */
    0x7c, 0x66, 0xaa, 0xe0,

    /* U+0039 "9" */
    0x4f, 0x9f, 0x36, 0x44,

    /* U+003A ":" */
    0xc8,

    /* U+003B ";" */
    0xa0,

    /* U+003C "<" */
    0x2a, 0x62,

    /* U+003D "=" */
    0xfc,

    /* U+003E ">" */
    0x45, 0xe0,

    /* U+003F "?" */
    0x74, 0xc4, 0x62, 0x0, 0x0,

    /* U+0040 "@" */
    0x3e, 0x20, 0xb6, 0xb6, 0xda, 0xec, 0xd9, 0x80,
    0x38,

    /* U+0041 "A" */
    0x1e, 0x6c, 0x9a, 0xfc, 0x70, 0x81, 0x0,

    /* U+0042 "B" */
    0x51, 0x24, 0x96, 0xca, 0x4b, 0x0,

    /* U+0043 "C" */
    0x3d, 0x8c, 0x20, 0x82, 0x7, 0x0,

    /* U+0044 "D" */
    0x19, 0x34, 0x71, 0x8a, 0x6a, 0x0,

    /* U+0045 "E" */
    0x39, 0xb1, 0x48, 0x43, 0x80,

    /* U+0046 "F" */
    0x3e, 0x1, 0x83, 0xc4, 0x8, 0x10, 0x0,

    /* U+0047 "G" */
    0x39, 0x8c, 0x26, 0x8a, 0x46, 0x0,

    /* U+0048 "H" */
    0x41, 0x63, 0x42, 0xda, 0xc6, 0x86, 0x84,

    /* U+0049 "I" */
    0x4d, 0x25, 0xa0,

    /* U+004A "J" */
    0x8, 0x30, 0x82, 0x18, 0xce, 0x0,

    /* U+004B "K" */
    0x24, 0xd9, 0x62, 0xcd, 0x99, 0x22, 0x0,

    /* U+004C "L" */
    0x23, 0x11, 0x8c, 0x43, 0xe0,

    /* U+004D "M" */
    0x18, 0xcb, 0xd2, 0x65, 0x99, 0x40, 0x70, 0x38,
    0xc,

    /* U+004E "N" */
    0x61, 0xb8, 0xd4, 0x49, 0x2c, 0xf6, 0x32, 0x8,

    /* U+004F "O" */
    0x30, 0xcf, 0xc, 0x38, 0x73, 0x9e, 0x0,

    /* U+0050 "P" */
    0x1d, 0x94, 0x57, 0xd3, 0x8, 0x0,

    /* U+0051 "Q" */
    0x7b, 0x18, 0x61, 0x96, 0x27, 0x40,

    /* U+0052 "R" */
    0x28, 0x96, 0xd2, 0x4b, 0x20, 0x80,

    /* U+0053 "S" */
    0x76, 0x10, 0xc1, 0x1b, 0x80,

    /* U+0054 "T" */
    0xf8, 0x82, 0x8, 0x21, 0x84, 0x0,

    /* U+0055 "U" */
    0xcf, 0x38, 0xa2, 0x9a, 0xc6, 0x0,

    /* U+0056 "V" */
    0x81, 0x8f, 0x16, 0x6c, 0x8f, 0x18, 0x0,

    /* U+0057 "W" */
    0x80, 0x22, 0x29, 0x9a, 0x64, 0xbb, 0x3b, 0x8c,
    0x40,

    /* U+0058 "X" */
    0x4d, 0x63, 0xc, 0x73, 0x68, 0x80,

    /* U+0059 "Y" */
    0x83, 0x35, 0x8, 0x20, 0x82, 0x0,

    /* U+005A "Z" */
    0x7c, 0x30, 0x84, 0x31, 0x8f, 0xc0,

    /* U+005B "[" */
    0x69, 0x6d, 0xb8,

    /* U+005C "\\" */
    0x86, 0x10, 0xc2, 0x8, 0x40,

    /* U+005D "]" */
    0x6d, 0xb4, 0xb0,

    /* U+005E "^" */
    0x31, 0x68, 0x40,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x20,

    /* U+0061 "a" */
    0x66, 0xa5, 0xc0,

    /* U+0062 "b" */
    0x42, 0x11, 0x8d, 0xc6, 0xe0,

    /* U+0063 "c" */
    0x68, 0x8e,

    /* U+0064 "d" */
    0x4, 0x30, 0x82, 0xea, 0x27, 0x0,

    /* U+0065 "e" */
    0x7f, 0x87,

    /* U+0066 "f" */
    0x39, 0x9, 0xe6, 0x21, 0x0,

    /* U+0067 "g" */
    0x74, 0xdc, 0x21, 0x78,

    /* U+0068 "h" */
    0x42, 0x10, 0xed, 0xca, 0x40,

    /* U+0069 "i" */
    0xca, 0x80,

    /* U+006A "j" */
    0x30, 0x22, 0x22, 0x6c,

    /* U+006B "k" */
    0x44, 0x4d, 0xea, 0xa0,

    /* U+006C "l" */
    0x57, 0xa8,

    /* U+006D "m" */
    0x40, 0xff, 0xc9, 0x99,

    /* U+006E "n" */
    0x3, 0xec, 0xa2,

    /* U+006F "o" */
    0xe4, 0x25, 0xc0,

    /* U+0070 "p" */
    0x59, 0x14, 0xfc, 0x82, 0x8, 0x0,

    /* U+0071 "q" */
    0x64, 0xa4, 0xa3, 0x10, 0x80,

    /* U+0072 "r" */
    0x8f, 0xc8,

    /* U+0073 "s" */
    0x68, 0x6f,

    /* U+0074 "t" */
    0x27, 0xc8, 0x84, 0x20,

    /* U+0075 "u" */
    0x4, 0xe7, 0xd0,

    /* U+0076 "v" */
    0x85, 0x99, 0x41, 0x0,

    /* U+0077 "w" */
    0x88, 0x9b, 0xee, 0x44,

    /* U+0078 "x" */
    0x93, 0x9d, 0x10,

    /* U+0079 "y" */
    0x4d, 0x21, 0x8, 0x42, 0x0,

    /* U+007A "z" */
    0xf2, 0x4f,

    /* U+007B "{" */
    0x24, 0x4c, 0x44, 0x60,

    /* U+007C "|" */
    0xfe,

    /* U+007D "}" */
    0x62, 0x23, 0x66, 0xc0,

    /* U+007E "~" */
    0x67, 0xb0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 140, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 59, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 79, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 124, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 105, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 17, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 47, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 30, .adv_w = 74, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 73, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 109, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 39, .adv_w = 99, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 41, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 42, .adv_w = 98, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 43, .adv_w = 55, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 109, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 124, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 95, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 124, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 105, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 118, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 99, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 79, .adv_w = 95, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 106, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 100, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 99, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 96, .adv_w = 56, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 97, .adv_w = 54, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 98, .adv_w = 76, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 79, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 101, .adv_w = 81, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 103, .adv_w = 103, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 168, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 117, .adv_w = 144, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 124, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 124, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 124, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 153, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 72, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 113, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 135, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 109, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 192, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 178, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 133, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 124, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 101, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 117, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 141, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 186, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 120, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 118, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 73, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 101, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 74, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 124, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 295, .adv_w = 100, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 54, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 297, .adv_w = 109, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 114, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 88, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 94, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 91, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 320, .adv_w = 107, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 324, .adv_w = 101, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 61, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 88, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 335, .adv_w = 98, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 64, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 153, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 115, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 98, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 357, .adv_w = 101, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 362, .adv_w = 97, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 89, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 103, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 113, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 159, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 105, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 123, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 389, .adv_w = 97, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 391, .adv_w = 89, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 51, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 97, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 2}
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
    -18, -18, -13, -34, -11, -11, -11, -16,
    -11, -11, -22, -7, -11, -11, -11, -16,
    -11, -9, -11, -11, -11, -11, -11, -11,
    -11, -11, -11, -11, -11, -11, -11, -7,
    -9, -22, -11, -11, -11, -13, -11, -27,
    -18, -11, -11, -18, -7, -4, -11, -7,
    -9, -9, -13, -11, -11, -27, -11, -9,
    -9, -18, -18, -13, -11, -7, -11, -7,
    -27, -18, -22, -18, -13, -7, -9, -27,
    -18, -11, -11, -22, -7, -22, -13, -7,
    -7, -11, -22, -18, -18, -18, -16, -34,
    -18, -13, -11, -22, -22, -18, -18, -18,
    -11, -11, -16, -11, -11, -27, -13, -9,
    -11, -9, -7, -27, -13, -7, -11, -11,
    -27, -13, -11, -9, -11, -9, -9, -9,
    -9, -11, -27, -11, -9, -11, -18, -18,
    -18, -16, -7, -7, -16, -7, -11, -7,
    -18, -16, -9, -16, -11, -13, -20, -9,
    -9, -34, -9, -11, -16, -22, -13, -13,
    -18, -11, -11, -9, -9, -9, -18, -11,
    -11, -11, -27, -18, -11, -7, -18, -7,
    -4, -27, -9, -18, -11, -13, -16, -7,
    -9, -7, -18, -4, -4, -9, -7, -18,
    -11, -11, -11, -11, -18, -7, -29, -7,
    -9, -11, -13, -7, -9, -18, -11, -11,
    -11, -11, -11, -11, -13, -11, -11, -9,
    -7, -7, -7, -27, -18, -11, -22, -18,
    -22, -22, -18, -18, -18, -18, -18, -27,
    -11, -18, -11, -18, -18, -13, -18, -7,
    -7, -7, -7, -7, -13, -11, -7, -7,
    -7, -11, -22, -11, -11, -11, -11, -9,
    -7, -11, -27, -11, -11, -7, -9, -9,
    -27, -18, -18, -18, -11, -27, -9, -9,
    -7, -7, -22, -11, -11, -22, -11, -11,
    -7, -7, -22, -22, -7, -22, -18, -22,
    -31, -18, -11, -34, -9, -18, -18, -22,
    -27, -22, -18, -27, -11, -16, -11, -18,
    -18, -22, -18, -18, -11, -7, -29, -11,
    -13, -18, -11, -22, -7, -7, -7, -22,
    -9, -7, -13, -7, -7, -22, -18, -11,
    -18, -18, -18, -11, -22, -18, -29, -9,
    -18, -11, -18, -22, -18, -18, -18, -11,
    -9, -11, -11, -18, -13, -11, -13, -18,
    -22, -7, -18, -4, -7, -7, -9, -22,
    -22, -9, -22, -22, -22, -9, -22, -9,
    -34, -7, -18, -18, -18, -22, -22, -22,
    -22, -9, -9, -9, -18, -18, -16, -11,
    -11, -9, -11, -16, -9, -16, -16, -18,
    -18, -29, -18, -11, -18, -18, -18, -18,
    -11, -18, -18, -22, -18, -9, -11, -18,
    -7, -11, -9, -9, -11, -22, -22, -18,
    -18, -18, -11, -22, -9, -11, -29, -9,
    -18, -11, -18, -22, -18, -18, -22, -18,
    -11, -18, -11, -18, -18, -25, -22, -9,
    -9, -22, -9, -9, -11, -11, -22, -9,
    -22, -7, -11, -7, -27, -9, -9, -27,
    -7, -9, -11, -18, -7, -9, -7, -11,
    -22, -22, -9, -7, -9, -22, -11, -11,
    -27, -7, -7, -11, -22, -11, -9, -13,
    -11, -25, -7, -11, -4, -11, -13, -9,
    -7, -11, -27, -7, -13, -13, -11, -9,
    -22, -9, -9, -11, -22, -9, -11, -22,
    -7, -9, -22, -9, -22, -11, -18, -9,
    -22, -7, -9, -22, -7, -11, -18, -11,
    -18, -9, -18, -18, -9, -7, -29, -9,
    -9, -7, -9, -18, -9, -9, -9, -11,
    -9, -22, -7, -11, -11, -7, -22, -11,
    -7, -7, -9, -7, -22, -9, -9, -22,
    -11, -11, -11, -18, -9, -22, -7, -22
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
const lv_font_t slacksideOne14 = {
#else
lv_font_t slacksideOne14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if SLACKSIDEONE14*/
