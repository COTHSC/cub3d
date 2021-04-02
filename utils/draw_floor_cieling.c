/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_cieling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:55:31 by jescully          #+#    #+#             */
/*   Updated: 2021/04/02 11:38:02 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		draw_cieling(t_vars *vars, int x, int draw_start)
{
	int i;

	i = 0;
	while (i < draw_start)
		vars->img->data[i++ * vars->res->w + x] = vars->res->c;
	return (1);
}

int		draw_floor(t_vars *vars, int x, int draw_end)
{
	int i;

	i = draw_end;
	while (i < vars->res->h)
		vars->img->data[i++ * vars->res->w + x] = vars->res->f;
	return (1);
}
