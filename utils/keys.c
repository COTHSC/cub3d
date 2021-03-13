/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:56:09 by jescully          #+#    #+#             */
/*   Updated: 2021/03/13 14:56:12 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		exit_game(t_vars *vars)
{
	int i;

	i = 0;
	free_sprites(vars);
	free(vars->p);
	free(vars->keys);
	i = 0;
	while (i < 4)
		mlx_destroy_image(vars->mlx, vars->text[i++]->ptr);
	i++;
	while (i < 4)
		free(vars->text[i++]);
	free(vars->map);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (1);
}

void	innit_keys(t_vars *vars)
{
	vars->keys->w = 0;
	vars->keys->s = 0;
	vars->keys->r = 0;
	vars->keys->l = 0;
	vars->keys->a = 0;
	vars->keys->d = 0;
}

int		key_press(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		exit_game(vars);
	if (keycode == 119)
		vars->keys->w = 1;
	if (keycode == 115)
		vars->keys->s = 1;
	if (keycode == 65363)
		vars->keys->r = 1;
	if (keycode == 65361)
		vars->keys->l = 1;
	if (keycode == 97)
		vars->keys->a = 1;
	if (keycode == 100)
		vars->keys->d = 1;
	return (0);
}

int		key_release(int keycode, t_vars *vars)
{
	if (keycode == 119)
		vars->keys->w = 0;
	if (keycode == 115)
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
