#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif


#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMAGE_POWER_RETURN
#define LV_ATTRIBUTE_IMAGE_POWER_RETURN
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMAGE_POWER_RETURN uint8_t Power_Return_map[] = {
  0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0c, 0x00,
  0x1c, 0x00, 0x3f, 0x80, 0x3f, 0xc0, 0x1f, 0xe0, 0x0c, 0xe0, 0x04, 0xe0, 0x00, 0xe0, 0x00, 0x60,
  0x00, 0x00, 0x00, 0x00,
};

const lv_image_dsc_t Power_Return = {
  .header.cf = LV_COLOR_FORMAT_I1,
  .header.magic = LV_IMAGE_HEADER_MAGIC,
  .header.stride = 2,
  .header.w = 14,
  .header.h = 14,
  .data_size = sizeof(Power_Return_map),
  .data = Power_Return_map,
};