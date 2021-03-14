/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecaster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:56:49 by jescully          #+#    #+#             */
/*   Updated: 2021/03/14 15:29:01 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void			dist_sprite(t_vars *vars, t_raysprite *r)
{
	while (++r->i < r->num_sprite)
		vars->sprites[r->i]->dist = ((vars->p->px - \
					vars->sprites[r->i]->x) * \
				(vars->p->px - vars->sprites[r->i]->x) + \
				(vars->p->py - vars->sprites[r->i]->y) * \
				(vars->p->py - vars->sprites[r->i]->y));
}

static	void		init_sprite_dir(t_vars *vars, t_raysprite *r)
{
	r->sx = vars->sprites[r->i]->x - vars->p->px;
	r->sy = vars->sprites[r->i]->y - vars->p->py;
	r->invd = 1.0 / (vars->p->plx * vars->p->dy - vars->p->dx * vars->p->ply);
	r->tx = r->invd * (vars->p->dy * r->sx - vars->p->dx * r->sy);
	r->ty = r->invd * (((-1) * vars->p->ply) * r->sx + vars->p->plx * r->sy);
	r->ssx = (int)((vars->res->w / 2) * (1 + r->tx / r->ty));
	r->sheight = abs((int)(vars->res->h / r->ty));
	r->dsy = -r->sheight / 2 + vars->res->h / 2;
}

static void			dr_sprite(t_vars *vars, t_raysprite *r, int texy, int texx)
{
	int				st;
	int				color;
	int				y;
	int				d;

	st = r->dsx;
	while (st < r->dex)
	{
		texx = (int)(256 * (st - (-r->swidth / 2 + r->ssx)) \
				* 64 / r->swidth) / 256;
		if (r->ty > 0 && st > 0 && st < vars->res->w \
				&& r->ty < r->zbuffer[st])
		{
			y = r->dsy - 1;
			while (++y < r->dey)
			{
				d = (y) * 256 - vars->res->h * 128 + r->sheight * 128;
				texy = ((d * 64) / r->sheight) / 256;
				color = vars->sprite->data[64 * texy + texx];
				if ((color & 0x00FFFFFF) != 0)
					vars->buf[y][st] = color;
			}
		}
		st++;
	}
}

static void			fill_raysprite(t_vars *vars, t_raysprite *r)
{
	if (r->dsy < 0)
		r->dsy = 0;
	r->dey = r->sheight / 2 + vars->res->h / 2;
	if (r->dey >= vars->res->h)
		r->dey = vars->res->h - 1;
	r->swidth = abs((int)(vars->res->h / r->ty));
	r->dsx = -r->swidth / 2 + r->ssx;
	if (r->dsx < 0)
		r->dsx = 0;
	r->dex = r->swidth / 2 + r->ssx;
	if (r->dex >= vars->res->w)
		r->dex = vars->res->w - 1;
}

int					spritecaster(t_vars *vars, int texx, int texy, double *zbuffer)
{
	t_raysprite		*r;

	r = malloc(sizeof(t_raysprite));
	r->num_sprite = count_sprites(vars);
	r->i = -1;
	dist_sprite(vars, r);
	r->zbuffer = zbuffer;
	sprite_sort(vars->sprites, r->num_sprite);
	r->i = -1;
	while (++r->i < r->num_sprite)
	{
		init_sprite_dir(vars, r);
		fill_raysprite(vars, r);
		dr_sprite(vars, r, texy, texx);
	}
	free(r);
	return (1);
}
