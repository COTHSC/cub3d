
#include "../cub3d.h"

void                    line_put(t_img *img, int x, int start, int end, int color)
{
        int i;

        i = start;
        while (i++ < end)
                pixel_put(img, x, i, color);
}
