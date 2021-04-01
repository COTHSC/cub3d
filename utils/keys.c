/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:56:09 by jescully          #+#    #+#             */
/*   Updated: 2021/04/01 13:27:39 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void free_error(t_vars *vars)
{
	int i;

	i = 0;
	while (i < 10)
		free(vars->error[i++]);
	free(vars->error);
}

void	free_farrayf(t_vars *vars)
{
	int i;

	i = 0;
	while (i < 8)
		free(vars->farray[i++]);
	free(vars->farray);
}

int             free_spritesf(t_vars *vars)
{
	int         num_sprites;
	int         i;

	num_sprites = count_sprites(vars);
	i = 0;
	while (i < num_sprites)
		free(vars->sprites[i++]);
//	free(vars->sprite);
	return (1);
}

int			exit_game(t_vars *vars, int bol, int error)
{
	if (vars->to_free->sprites)
		free_spritesf(vars);
	if (bol > 0)
		little_free(vars);
	if (bol > 1)
		big_free(vars);
	if (error != 7)
		printf("Error\n%s\n", vars->error[error]);
	else
		printf("game exited succesfully\n");
	free_error(vars);
	if (vars->to_free->farray)
		free_farrayf(vars);
	free(vars->to_free);
	exit(0);
	return (1);
}

void		innit_keys(t_vars *vars)
{
	vars->keys->w = 0;
	vars->keys->s = 0;
	vars->keys->r = 0;
	vars->keys->l = 0;
	vars->keys->a = 0;
	vars->keys->d = 0;
}

int			key_press(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		exit_game(vars, 2, 7);
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

int			key_release(int keycode, t_vars *vars)
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
