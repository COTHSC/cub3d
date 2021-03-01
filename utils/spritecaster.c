#include "../cub3d.h"

#define numSprites 8

int     sprite_sort(t_sprites **sprite, int num_sprites)
{
	int i = 0;
	int done = 0;
	t_sprites *dummy;

	dummy = malloc(sizeof(t_sprites));
	while(i < num_sprites - 1)
	{
		if (sprite[i]->dist < sprite[i + 1]->dist)
		{
			dummy->dist = sprite[i + 1]->dist;
			sprite[i + 1]->dist = sprite[i]->dist;
			sprite[i]->dist = dummy->dist;
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


int     spritecaster(t_vars *vars, int texX, int texY, int texNum, int zbuffer[640])
{
	int i = 0;
    t_sprites **sprite;
	int num_sprite = 3;

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
	int     h = screenHeight;
	int     w = screenWidth;
	int     spriteHeight;
	int     spriteWidth;
	int color;

    sprite = malloc(sizeof(t_sprites *));
//	i = 0;
//	while( i < num_sprite )
//	{
//		sprite[i] = malloc(sizeof(t_sprites));
//		i++;
//	}


//	innit_sprites(sprite, 10.5, 11.5, 0);
//	innit_sprites(sprite, 10.5, 20.5, 1);
//	innit_sprites(sprite, 20.5, 11.5, 2);

    spritefinder(sprite, vars->WorldMap);
	i = 0;
	while (i < num_sprite)
	{
		sprite[i]->dist = ((vars->pos->posX - sprite[i]->x) * (vars->pos->posX - sprite[i]->x) + (vars->pos->posY - sprite[i]->y) * (vars->pos->posY - sprite[i]->y));
		i++;
	}
	sprite_sort(sprite, num_sprite);


	i = 0;

	while(i < num_sprite)
	{
		spriteX = sprite[i]->x - vars->pos->posX;
		spriteY = sprite[i]->y - vars->pos->posY;
		invDet = 1.0 / (vars->pos->planeX * vars->pos->dirY - vars->pos->dirX * vars->pos->planeY);
		transformX = invDet * (vars->pos->dirY * spriteX - vars->pos->dirX * spriteY);
		transformY = invDet * (-vars->pos->planeY * spriteX + vars->pos->planeX * spriteY);
		spriteScreenX = (int)((screenWidth / 2) * (1 + transformX / transformY)); 

		spriteHeight = abs((int)(h / transformY));
		drawStartY = -spriteHeight / 2 + h / 2;
		if (drawStartY< 0)
			drawStartY = 0;
		drawEndY = spriteHeight / 2 + h / 2;
		if (drawEndY >= h)
			drawEndY = screenHeight - 1;

		spriteWidth = abs((int)(h / transformY));
		drawStartX = -spriteWidth / 2 + spriteScreenX;
		if (drawStartX< 0)
			drawStartX = 0;
		drawEndX = spriteWidth / 2 + spriteScreenX;
		if (drawEndX >= w)
			drawEndX = screenWidth - 1;
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

