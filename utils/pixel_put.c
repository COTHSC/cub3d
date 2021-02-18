#include "../cub3d.h"

void            pixel_put(t_img *image, int x, int y, int color)
{
        unsigned char *src;
        unsigned char r;
        unsigned char g;
        unsigned char b;

        src = (unsigned char *)&color;
        r = src[0];
        g = src[1];
        b = src[2];
        image->data[y * image->size_l + x * image->bpp / 8] = r;
        image->data[y * image->size_l + x * image->bpp / 8 + 1] = g;
        image->data[y * image->size_l + x * image->bpp / 8 + 2] = b;
}
