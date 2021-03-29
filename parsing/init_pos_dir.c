/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pos_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:23:04 by jescully          #+#    #+#             */
/*   Updated: 2021/03/17 14:42:00 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

int			init_orientation(t_vars *vars, double h)
{
	double	opx;
	double	odx;

	if (h == 0)
		return (0);
	odx = vars->p->dx;
	vars->p->dx = vars->p->dx * cos(h) - vars->p->dy * sin(h);
	vars->p->dy = odx * sin(h) + vars->p->dy * cos(-h);
	opx = vars->p->plx;
	vars->p->plx = vars->p->plx * cos(h) - vars->p->ply * sin(h);
	vars->p->ply = opx * sin(h) + vars->p->ply * cos(h);
	return (0);
}

int			save_position(t_vars *vars, char c, int h, int i)
{
	double rot;

	if (c == 'N')
		rot = 0;
	else if (c == 'S')
		rot = M_PI;
	else if (c == 'E')
		rot = 3 * M_PI / 2;
	else if (c == 'W')
		rot = M_PI / 2;
	vars->p->px = (double)h + 0.5;
	vars->p->py = (double)i - 0.5;
	vars->p->dx = -1;
	vars->p->dy = 0;
	vars->p->plx = 0;
	vars->p->ply = 0.66;
	vars->p->ms = 0.08;
	vars->p->rs = 0.03;
	init_orientation(vars, rot);
	return (1);
}
