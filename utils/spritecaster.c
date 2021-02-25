#include "../cub3d.h"

int     innit_sprites(t_sprites **sprite, double x, double y, int num)
{
    sprite[num]->x = x;
    sprite[num]->y = y;
    sprite[num]->dist = 0;
    return (1);
}


int     sprite_sort(t_sprites **sprite, int num_sprite)
{
    int i = 0;
    int done = 0;
    t_sprites *dummy;

    dummy = malloc(sizeof(t_sprites));
    while(i < num_sprite - 1)
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
        sprite_sort(sprite, num_sprite);
    else
        return (1);
    return (1);
}


int     spritecaster(t_pos *pos)
{
    int i = 0;
    t_sprites **sprite;
    int num_sprite = 3;
    double spriteX;
    double spriteY;
    double invDet;
    double transformX;
    double transformY;

    sprite = malloc(sizeof(t_sprites *));

    while( i < num_sprite )
    {
        sprite[i] = malloc(sizeof(t_sprites));
        i++;
    }


    innit_sprites(sprite, 10.5, 11.5, 0);
    innit_sprites(sprite, 10.5, 20.5, 1);
    innit_sprites(sprite, 20.5, 11.5, 2);


    i = 0;
    while (i < num_sprite)
    {
        sprite[i]->dist = ((pos->posX - sprite[i]->x) * (pos->posX - sprite[i]->x) + (pos->posY - sprite[i]->y) * (pos->posY - sprite[i]->y));
        i++;
    }
    sprite_sort(sprite, num_sprite);

    while(i < num_sprite)
    {
        spriteX = sprite[i]->x - pos->posX;
        spriteY = sprite[i]->y - pos->posY;
        invDet = 1.0 / (pos->planeX * pos->dirY - pos->dixX * pos->planeY);
        transformX = invDet * (pos->dirY * spriteX - pos->dirX * spriteY);
        transformY = invDet * (pos->planeY * spriteX - pos->planeX * spriteY);

    }

    return (1);

}
