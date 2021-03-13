/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:54:31 by jescully          #+#    #+#             */
/*   Updated: 2021/03/13 14:54:37 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				dda(t_vars *vars, t_raycast *r)
{
	int			side;
	int			hit;

	hit = 0;
	while (hit == 0)
	{
		if (r->sdx < r->sdy)
		{
			r->sdx += r->ddx;
			r->mapx += r->stpx;
			side = 0;
		}
		else
		{
			r->sdy += r->ddy;
			r->mapy += r->stpy;
			side = 1;
		}
		if (*(vars->map + sia(vars->collumn, r->mapx) + r->mapy) == 1)
			hit = 1;
	}
	r->lineh = calc_line_height(vars, r, side);
	r->draws = -r->lineh / 2 + vars->res->h / 2;
	return (side);
}

static void		calc_steps(t_vars *vars, t_raycast *r)
{
	if (r->rdirx < 0)
	{
		r->stpx = -1;
		r->sdx = (vars->p->px - r->mapx) * r->ddx;
	}
	else
	{
		r->stpx = 1;
		r->sdx = (r->mapx + 1.0 - vars->p->px) * r->ddx;
	}
	if (r->rdiry < 0)
	{
		r->stpy = -1;
		r->sdy = (vars->p->py - r->mapy) * r->ddy;
	}
	else
	{
		r->stpy = 1;
		r->sdy = (r->mapy + 1.0 - vars->p->py) * r->ddy;
	}
}

void			fill_buffer(t_vars *vars, t_raycast *r, int y, int tn)
{
	int color;

	while (y < r->drawe)
	{
		r->texy = (int)r->texp & (vars->text[tn]->height - 1);
		r->texp += r->stp;
		color = vars->text[tn]->data[vars->text[tn]->width * r->texy + r->texx];
		vars->buf[y][r->i] = color;
		y++;
	}
}

static void		draw_wall(t_vars *vars, t_raycast *r, int side, int tn)
{
	int y;

	y = 0;
	if (r->draws < 0)
		r->draws = 0;
	r->drawe = r->lineh / 2 + vars->res->h / 2;
	if (r->drawe >= vars->res->h || r->drawe < 0)
		r->drawe = vars->res->h - 1;
	if (side == 0)
		r->wx = vars->p->py + r->pwd * r->rdiry;
	else
		r->wx = vars->p->px + r->pwd * r->rdirx;
	r->wx -= floor(r->wx);
	tn = get_texnum(r, side);
	r->texx = (int)(r->wx * (double)vars->text[tn]->width);
	r->texx = vars->text[tn]->width - r->texx - 1;
	r->stp = 1.0 * vars->text[tn]->height / r->lineh;
	r->texp = (r->draws - (vars->res->h / 2) + (r->lineh / 2)) * r->stp;
	y = r->draws;
	fill_buffer(vars, r, y, tn);
}

void			draw_frame(t_vars *vars)
{
	int			*zbuffer;
	t_raycast	*r;
	int			side;
	int			tn;

	side = 0;
	tn = 0;
	r = malloc(sizeof(t_raycast));
	zbuffer = malloc(sizeof(int) * vars->res->w);
	prep_image(vars);
	r->i = -1;
	while (++r->i < vars->res->w - 1)
	{
		init_dirs(vars, r);
		calc_steps(vars, r);
		side = dda(vars, r);
		draw_wall(vars, r, side, tn);
		draw_cieling(vars, r->i, r->draws);
		draw_floor(vars, r->i, r->drawe);
		zbuffer[r->i] = r->pwd;
	}
	spritecaster(vars, r->texx, r->texy, zbuffer);
	free(zbuffer);
	free(r);
	draw(vars);
}
