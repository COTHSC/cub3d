#include "../cub3d.h"
/*
void            pixel_put(t_img *img, int x, int y, char color)
{
    unsigned int    *src;
    unsigned char    r;
    unsigned char    g;
    unsigned char    b;

    printf("color %x\n", color);
    src = (unsigned int *)&color;
    r = src[0];
    g = src[1];
    b = src[2];
    printf("pre tx_addr\n");
    img->data[y * img->size_l + x * img->bpp / 8] = r;
    img->data[y * img->size_l + x * img->bpp / 8 + 1] = g;
    img->data[y * img->size_l + x * img->bpp / 8 + 2] = b;
    printf("post tx_addr\n");
}
*/
void            pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->data + (y * img->size_l + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}
