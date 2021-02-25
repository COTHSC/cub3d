#include "../cub3d.h"

void    reset_buffer(t_vars *vars)
{
        for (int y = 0; y < screenHeight; y++)
        {
                for (int x = 0; x < screenWidth; x++)
                        vars->buf[y][x] = 0;
        }
}
