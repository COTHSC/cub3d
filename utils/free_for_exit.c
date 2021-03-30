/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_for_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:39:32 by jean              #+#    #+#             */
/*   Updated: 2021/03/30 12:30:53 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_config(t_res *res)
{
	if (res->NO)
		free(res->NO);
	if (res->EA)
		free(res->EA);
	if (res->SO)
		free(res->SO);
	if (res->WE)
		free(res->WE);
	if (res->S)
		free(res->S);
}

void		little_free(t_vars *vars)
{
	if (vars->res)
	{
		free_config(vars->res);
		free(vars->res);
	}
	if (vars->p)
		free(vars->p);
	if (vars->keys)
		free(vars->keys);
	if (*vars->map == 1 || *vars->map == 3 || *vars->map == 7 || *vars->map == 5)
	{
		free(vars->map);
		free(vars->collumn);
	}
}

void		big_free(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < 4)
		mlx_destroy_image(vars->mlx, vars->text[i++]->ptr);
	mlx_destroy_image(vars->mlx, vars->sprite->ptr);
	free(vars->sprite);
	i = 0;
	while (i < 4)
		free(vars->text[i++]);
	if (!vars->save)
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
	}
	else
	{
		mlx_destroy_image(vars->mlx, vars->img->ptr);
		free(vars->img);
	}
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}
