#include "../cub3d.h"

int     sprite_sort(t_sprites **sprite, int num_sprites)
{
	int i = 0;
	int done = 0;
	t_sprites *dummy;

	dummy = malloc(sizeof(t_sprites));
	dummy->dist = 0;
	dummy->x = 0.0;
	dummy->y = 0.0;
	while(i < num_sprites - 1)
	{
		if (sprite[i]->dist < sprite[i + 1]->dist)
		{
			dummy->dist = sprite[i + 1]->dist;
			dummy->x = sprite[i + 1]->x;
			dummy->y = sprite[i + 1]->y;
			sprite[i + 1]->dist = sprite[i]->dist;
			sprite[i + 1]->x = sprite[i]->x;
			sprite[i + 1]->y = sprite[i]->y;
			sprite[i]->dist = dummy->dist;
			sprite[i]->x = dummy->x;
			sprite[i]->y = dummy->y;
			done++;
		}
		i++;
	}   
    free(dummy);
	if (done != 0)
		sprite_sort(sprite, num_sprites);
	else
		return (1);
	return (1);
}

int     count_sprites(t_vars *vars)
{
    int h = 0;
    int w = 0;
    int num_sprite;

    num_sprite = 0;
    while(h < vars->map_h)
    {
        w = 0;
        while(w < vars->collumn[h])
        {
            if (get_value(vars, h, w) == 2)
                num_sprite++;
            w++;
        }
        h++;
    }
    return (num_sprite);
}

int     init_sprites(t_vars *vars)
{

	int i = 0;
	int num_sprite;

    num_sprite = count_sprites(vars);
    vars->sprites = malloc(sizeof(t_sprites) * num_sprite);
	i = 0;
    while( i < num_sprite)
        vars->sprites[i++] = malloc(sizeof(t_sprites));
    spritefinder(vars->sprites, vars);
	return (1);
}

int     free_sprites(t_vars *vars)
{
	int num_sprites;
	int i;

    num_sprites = count_sprites(vars);
	i = 0;
	while(i < num_sprites)
		free(vars->sprites[i++]);
    free(vars->sprites);
	return (1);
}

typedef	struct	s_raysprite
{
	double sx;
	double sy;
	double invd;
	double tx;
	double ty;
	int     ssx;
	int     dsx;
	int     dsy;
	int     dey;
	int     dex;
	int     sheight;
	int     swidth;
	int     i;
	int num_sprite;
}	t_raysprite;

static void	dist_sprite(t_vars * vars, t_raysprite *r)
{
	while (++r->i < r->num_sprite)
		vars->sprites[r->i]->dist = ((vars->p->px - vars->sprites[r->i]->x) * \
				(vars->p->px - vars->sprites[r->i]->x) + (vars->p->py - vars->sprites[r->i]->y) * (vars->p->py - vars->sprites[r->i]->y));
}

static	void	init_sprite_dir(t_vars *vars, t_raysprite *r)
{
		r->sx = vars->sprites[r->i]->x - vars->p->px;
		r->sy = vars->sprites[r->i]->y - vars->p->py;
		r->invd = 1.0 / (vars->p->plx * vars->p->dy - vars->p->dx * vars->p->ply);
		r->tx = r->invd * (vars->p->dy * r->sx - vars->p->dx * r->sy);
		r->ty = r->invd * (-vars->p->ply * r->sx + vars->p->plx * r->sy);
		r->ssx = (int)((vars->res->w / 2) * (1 + r->tx / r->ty)); 
		r->sheight = abs((int)(vars->res->h / r->ty));
		r->dsy = -r->sheight / 2 + vars->res->h / 2;
}

int     spritecaster(t_vars *vars, int texX, int texY, int *zbuffer)
{
	int color;
	t_raysprite	*r;
	int     h = vars->res->h;
	int     w = vars->res->w;
	
	r = malloc(sizeof(t_raysprite));
    r->num_sprite = count_sprites(vars);
	r->i = -1;
	dist_sprite(vars,r);
    sprite_sort(vars->sprites, r->num_sprite);
	r->i = -1;
	while(++r->i < r->num_sprite)
	{
		init_sprite_dir(vars, r);
		if (r->dsy< 0)
			r->dsy = 0;
		r->dey = r->sheight / 2 + h / 2;
		if (r->dey >= h)
			r->dey = vars->res->h - 1;

		r->swidth = abs((int)(h / r->ty));
		r->dsx = -r->swidth / 2 + r->ssx;
		if (r->dsx< 0)
			r->dsx = 0;
		r->dex = r->swidth / 2 + r->ssx;
		if (r->dex >= w)
			r->dex = vars->res->w - 1;
		for(int stripe = r->dsx; stripe < r->dex; stripe++)
		{
			texX = (int)(256 * (stripe - (-r->swidth / 2 + r->ssx)) * 64 / r->swidth) / 256;
			if(r->ty > 0 && stripe > 0 && stripe < w && r->ty < zbuffer[stripe])
				for(int y = r->dsy; y < r->dey; y++)
				{
					int d = (y) * 256 - h * 128 + r->sheight * 128;
					texY = ((d * 64) / r->sheight) / 256;
					color = vars->sprite->data[64 * texY + texX]; 
					if((color & 0x00FFFFFF) != 0) vars->buf[y][stripe] = color; 
				}
		}
	}
	free(r);
	return (1);
}
