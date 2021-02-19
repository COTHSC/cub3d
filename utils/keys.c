#include "../cub3d.h"

int	exit_game(t_vars *vars)
{
	int i = 0;

	free(vars->pos);
	free(vars->keys);
	i = 0;
	while (i < 8)
		mlx_destroy_image(vars->mlx, vars->text[i++]->ptr);
	i++;
	while (i < 8)
		free(vars->text[i++]);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (1);
}

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		exit_game(vars);
	if (keycode == 65362)
		vars->keys->w = 1;
	if (keycode == 65364)
		vars->keys->s = 1;
	if (keycode == 65363)
		vars->keys->r = 1;
	if (keycode == 65361)
		vars->keys->l = 1;
	if (keycode == 97)
		vars->keys->a = 1;
	if (keycode == 100)
		vars->keys->d = 1;
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
	if (keycode == 97)
		vars->keys->a = 0;
	if (keycode == 100)
		vars->keys->d = 0;
	return (1);
}

int	button_press(int buttoncode, t_vars *vars)
{
	printf("this is the buttoncode hopefully? %i \n", buttoncode);
	return (1);
}
