#include "../cub3d.h"

static int		calc_line_height(t_vars *vars, t_raycast *r, int side)
{
	int			lineh;

	if (side == 0)
		r->pwd = (r->mapx - vars->p->px + (1 - r->stpx) / 2) / r->rdirx;
	else
		r->pwd = (r->mapy - vars->p->py + (1 - r->stpy) / 2) / r->rdiry;
	lineh = (int)(vars->res->h / r->pwd);
	return (lineh);
}

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

static void		init_dirs(t_vars *vars, t_raycast *r)
{
	r->camx = (2 * r->i) / ((double)vars->res->w) - 1;
	r->rdirx = vars->p->dx + vars->p->plx * r->camx;
	r->rdiry = vars->p->dy + vars->p->ply * r->camx;
	r->mapx = (int)vars->p->px;
	r->mapy = (int)vars->p->py;
	r->ddx = fabs(1 / r->rdirx);
	r->ddy = fabs(1 / r->rdiry);
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

static int		get_texnum(t_raycast *r, int side)
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

void			prep_image(t_vars *vars)
{
	vars->img = malloc(sizeof(t_img));
	vars->img->ptr = mlx_new_image(vars->mlx, vars->res->w, vars->res->h);
	vars->img->data = \
			(int *)mlx_get_data_addr(vars->img->ptr, &vars->img->bpp, \
			&vars->img->size_l, &vars->img->endian);
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
