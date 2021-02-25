#include "../cub3d.h"

void    draw(t_vars *vars)
{

    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++)
            vars->img->data[y * screenWidth + x] = vars->buf[y][x];
    }

    reset_buffer(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->ptr, 0, 0);
    mlx_destroy_image(vars->mlx, vars->img->ptr);
    free(vars->img);
}
