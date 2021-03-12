#include "../cub3d.h"

void	draw(t_vars *vars)
{
	int y;
	int x;

	y = 0;
	while (y < vars->res->h)
	{
		x = 0;
		while (x < vars->res->w)
		{
			vars->img->data[y * vars->res->w + x] = vars->buf[y][x];
			x++;
		}
		y++;
	}
	//save_img(vars, "constchar");
	reset_buffer(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	free(vars->img);
}
