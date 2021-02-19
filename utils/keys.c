#include "../cub3d.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 65362)
		vars->keys->w = 1;
	if (keycode == 65364)
		vars->keys->s = 1;
	if (keycode == 65363)
		vars->keys->r = 1;
	if (keycode == 65361)
		vars->keys->l = 1;
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	printf("this is key press\n");
	return (1);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == 65362)
		vars->keys->w = 0;
	if (keycode == 65364)
		vars->keys->s = 0;
	if (keycode == 65363)
		vars->keys->r = 0;
	if (keycode == 65361)
		vars->keys->l = 0;

	printf("this is key release\n");
	return (1);
}
