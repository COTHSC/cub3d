/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:56:20 by jescully          #+#    #+#             */
/*   Updated: 2021/03/13 14:58:11 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				calc_line_height(t_vars *vars, t_raycast *r, int side)
{
	int			lineh;

	if (side == 0)
		r->pwd = (r->mapx - vars->p->px + (1 - r->stpx) / 2) / r->rdirx;
	else
		r->pwd = (r->mapy - vars->p->py + (1 - r->stpy) / 2) / r->rdiry;
	lineh = (int)(vars->res->h / r->pwd);
	return (lineh);
}

void			init_dirs(t_vars *vars, t_raycast *r)
{
	r->camx = (2 * r->i) / ((double)vars->res->w) - 1;
	r->rdirx = vars->p->dx + vars->p->plx * r->camx;
	r->rdiry = vars->p->dy + vars->p->ply * r->camx;
	r->mapx = (int)vars->p->px;
	r->mapy = (int)vars->p->py;
	r->ddx = fabs(1 / r->rdirx);
	r->ddy = fabs(1 / r->rdiry);
}

int				get_texnum(t_raycast *r, int side)
{
	if (side == 0 && r->rdirx >= 0)
		return (0);
	else if (side == 0 && r->rdirx < 0)
		return (1);
	else if (side == 1 && r->rdiry >= 0)
		return (2);
	else
		return (3);
}

void			prep_image(t_vars *vars)
{
	vars->img = malloc(sizeof(t_img));
	vars->img->ptr = mlx_new_image(vars->mlx, vars->res->w, vars->res->h);
	vars->img->data = \
			(int *)mlx_get_data_addr(vars->img->ptr, &vars->img->bpp, \
			&vars->img->size_l, &vars->img->endian);
}
