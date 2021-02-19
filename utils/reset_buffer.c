#include "../cub3d.h"

void    reset_buffer(t_vars *vars)
{
        for (int y = 0; y < 480; y++)
        {
                for (int x = 0; x < 640; x++)
                        vars->buf[y][x] = 0;
        }
}
