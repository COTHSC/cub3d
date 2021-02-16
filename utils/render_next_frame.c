
#include "../cub3d.h"

int     render_next_frame(t_vars *vars)
{
    void *imgt2;
	imgt2 = mlx_new_image(vars->mlx, 640, 480);	
	mlx_put_image_to_window(vars->mlx, vars->win, imgt2, 0, 0);
	mlx_destroy_image(vars->mlx, imgt2);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->ptr, vars->pos->posX, vars->pos->posY);
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	return (1);
}

