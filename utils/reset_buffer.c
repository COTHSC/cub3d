#include "../cub3d.h"

void	reset_buffer(t_vars *vars)
{
	int y;
	int x;

	y = 0;
	while (y < vars->res->h)
	{
		x = 0;
		while (x < vars->res->w)
		{
			vars->buf[y][x] = 0;
			x++;
		}
		y++;
	}
}
