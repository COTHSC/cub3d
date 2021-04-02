/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 08:45:49 by jescully          #+#    #+#             */
/*   Updated: 2021/04/02 08:58:00 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void		free_error(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < 10)
		free(vars->error[i++]);
	free(vars->error);
}

void		free_farrayf(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < 8)
		free(vars->farray[i++]);
	free(vars->farray);
}

int			free_spritesf(t_vars *vars)
{
	int		num_sprites;
	int		i;

	num_sprites = count_sprites(vars);
	i = 0;
	while (i < num_sprites)
		free(vars->sprites[i++]);
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
