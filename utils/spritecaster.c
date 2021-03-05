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
	if (done != 0)
		sprite_sort(sprite, num_sprites);
	else
		return (1);
	return (1);
}

int     count_sprites(int **map)
{
    int h = 0;
    int w = 0;
    int num_sprite;

    num_sprite = 0;
    while(h < 24)
    {
        w = 0;
        while(w < 24)
        {
            if (map[h][w] == 2)
                num_sprite++;
            w++;
        }
        h++;
    }
    return (num_sprite);
}

int     spritecaster(t_vars *vars, int texX, int texY, int texNum, int zbuffer[640])
{
	int i = 0;
    t_sprites **sprite;
	int num_sprite;

	double spriteX;
	double spriteY;
	double invDet;
	double transformX;
	double transformY;
	int     spriteScreenX;
	int     drawStartX;
	int     drawStartY;
	int     drawEndY;
	int     drawEndX;
	int     h = vars->res->h;
	int     w = vars->res->w;
	int     spriteHeight;
	int     spriteWidth;
	int color;

    num_sprite = count_sprites(vars->WorldMap);
    sprite = malloc(sizeof(t_sprites *) * num_sprite);
	i = 0;
	while( i < num_sprite )
	{
		sprite[i] = malloc(sizeof(t_sprites));
		i++;
	}


//	innit_sprites(sprite, 10.5, 11.5, 0);
//	innit_sprites(sprite, 10.5, 20.5, 1);
//	innit_sprites(sprite, 20.5, 11.5, 2);

    spritefinder(sprite, vars->WorldMap);
	i = 0;
	while (i < num_sprite)
	{
		sprite[i]->dist = ((vars->p->px - sprite[i]->x) * (vars->p->px - sprite[i]->x) + (vars->p->py - sprite[i]->y) * (vars->p->py - sprite[i]->y));
		i++;
	}
	sprite_sort(sprite, num_sprite);


	i = 0;

	while(i < num_sprite)
	{
		spriteX = sprite[i]->x - vars->p->px;
		spriteY = sprite[i]->y - vars->p->py;
		invDet = 1.0 / (vars->p->plx * vars->p->dy - vars->p->dx * vars->p->ply);
		transformX = invDet * (vars->p->dy * spriteX - vars->p->dx * spriteY);
		transformY = invDet * (-vars->p->ply * spriteX + vars->p->plx * spriteY);
		spriteScreenX = (int)((vars->res->w / 2) * (1 + transformX / transformY)); 

		spriteHeight = abs((int)(h / transformY));
		drawStartY = -spriteHeight / 2 + h / 2;
		if (drawStartY< 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + h / 2;
		if (drawEndY >= h)
			drawEndY = vars->res->h - 1;

		spriteWidth = abs((int)(h / transformY));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX< 0)
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= w)
			drawEndX = vars->res->w - 1;
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 64 / spriteWidth) / 256;
			if(transformY > 0 && stripe > 0 && stripe < w && transformY < zbuffer[stripe])
				for(int y = drawStartY; y < drawEndY; y++)
				{
					int d = (y) * 256 - h * 128 + spriteHeight * 128;
					texY = ((d * 64) / spriteHeight) / 256;
					color = vars->sprite->data[64 * texY + texX]; 
					if((color & 0x00FFFFFF) != 0) vars->buf[y][stripe] = color; 
				}
		}
		i++;
	}
	return (1);

}

