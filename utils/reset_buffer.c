#include "../cub3d.h"

void    reset_buffer(t_vars *vars)
{
        for (int y = 0; y < vars->res->h; y++)
        {
                for (int x = 0; x < vars->res->w; x++)
                        vars->buf[y][x] = 0;
        }
}
