#include "img_resize.h"
#include <cstdlib>

void image_downscale(const uint8_t *src, uint8_t *dst, int src_w, int src_h, int dst_w, int dst_h)
{
    int src_stride = (src_w + 7) / 8;
    int dst_stride = (dst_w + 7) / 8;
    memset(dst, 0, dst_stride * dst_h);

    for (int by = 0; by < dst_h; by++)
    {
        int sy0 = (by * src_h) / dst_h;
        int sy1 = ((by + 1) * src_h) / dst_h;
        if (sy1 <= sy0)
            sy1 = sy0 + 1;

        for (int bx = 0; bx < dst_w; bx++)
        {
            int sx0 = (bx * src_w) / dst_w;
            int sx1 = ((bx + 1) * src_w) / dst_w;
            if (sx1 <= sx0)
                sx1 = sx0 + 1;

            int count = 0;
            int total = (sy1 - sy0) * (sx1 - sx0);

            for (int sy = sy0; sy < sy1; sy++)
            {
                const uint8_t *row = &src[sy * src_stride];
                for (int sx = sx0; sx < sx1; sx++)
                {
                    count += (row[sx >> 3] >> (7 - (sx & 7))) & 1;
                }
            }

            if (count * 2 >= total)
            {
                dst[by * dst_stride + (bx >> 3)] |= (0x080 >> (bx & 7));
            }
        }
    }
}

void downscale(const uint8_t *src, uint8_t *dst, int src_w, int src_h, int dst_w, int dst_h)
{
    int dst_stride = (dst_w + 7) / 8;
    uint8_t *dst_buf = (uint8_t *)malloc(dst_stride * dst_h);   // <-- malloc lives here
    image_downscale(src, dst_buf, src_w, src_h, dst_w, dst_h);
    memcpy(dst, dst_buf, dst_stride * dst_h);
    free(dst_buf);
}