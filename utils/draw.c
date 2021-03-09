#include "../cub3d.h"

void    draw(t_vars *vars)
{
    for (int y = 0; y < vars->res->h; y++)
    {
        for (int x = 0; x < vars->res->w; x++)
            vars->img->data[y * vars->res->w + x] = vars->buf[y][x];
    }
    save_img(vars, "constchar");
    reset_buffer(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->ptr, 0, 0);
    mlx_destroy_image(vars->mlx, vars->img->ptr);
    free(vars->img);
}
