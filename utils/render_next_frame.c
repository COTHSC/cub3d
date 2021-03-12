#include "../cub3d.h"

int	render_next_frame(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->img->ptr, vars->p->px, vars->p->py);
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	return (1);
}
