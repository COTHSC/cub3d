/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:55:51 by jescully          #+#    #+#             */
/*   Updated: 2021/03/13 14:55:54 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			get_value(t_vars *vars, int h, int w)
{
	int		i;

	i = 0;
	i = *(vars->map + sia(vars->collumn, h) + w);
	return (i);
}

static void	rotate(t_vars *v)
{
	double	opx;
	double	odx;
	t_pos	*p;

	p = v->p;
	if (v->keys->r)
	{
		odx = p->dx;
		p->dx = p->dx * cos(-1 * p->rs) - p->dy * sin(-1 * p->rs);
		p->dy = odx * sin(-p->rs) + p->dy * cos(-p->rs);
		opx = p->plx;
		p->plx = p->plx * cos(-1 * (p->rs)) - p->ply * sin(-1 * (p->rs));
		p->ply = opx * sin(-1 * p->rs) + p->ply * cos(-1 * p->rs);
	}
	if (v->keys->l)
	{
		odx = p->dx;
		p->dx = p->dx * cos(p->rs) - p->dy * sin(p->rs);
		p->dy = odx * sin(p->rs) + p->dy * cos(-p->rs);
		opx = p->plx;
		p->plx = p->plx * cos(p->rs) - p->ply * sin(p->rs);
		p->ply = opx * sin(p->rs) + p->ply * cos(p->rs);
	}
}

static void	strafe(t_vars *v)
{
	t_pos	*p;

	p = v->p;
	if (v->keys->d)
	{
		if (get_value(v, (int)(p->px + p->plx * p->ms), (int)p->py) == 3)
			p->px += p->plx * p->ms;
		if (get_value(v, (int)p->px, (int)(p->py + p->ply * p->ms)) == 3)
			p->py += p->ply * p->ms;
	}
	if (v->keys->a)
	{
		if (get_value(v, (int)(p->px - p->plx * p->ms), (int)p->py) == 3)
			p->px -= p->plx * p->ms;
		if (get_value(v, (int)p->px, (int)(p->py - p->ply * p->ms)) == 3)
			p->py -= p->ply * p->ms;
	}
}

int			key_hook(t_vars *v)
{
	t_pos	*p;

	p = v->p;
	if (v->keys->w)
	{
		if (get_value(v, (int)(p->px + p->dx * p->ms), (int)p->py) == 3)
			p->px += p->dx * p->ms;
		if (get_value(v, (int)p->px, (int)(p->py + p->dy * p->ms)) == 3)
			p->py += p->dy * p->ms;
	}
	if (v->keys->s)
	{
		if (get_value(v, (int)(p->px - p->dx * p->ms), (int)p->py) == 3)
			p->px -= p->dx * p->ms;
		if (get_value(v, (int)p->px, (int)(p->py - p->dy * p->ms)) == 3)
			p->py -= p->dy * p->ms;
	}
	strafe(v);
	rotate(v);
	draw_frame(v);
	return (1);
}
