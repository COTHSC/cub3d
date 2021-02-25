#include "../cub3d.h"

#define numSprites 8

t_sprites sprite[numSprites] =
{

    //some barrels around the map
    {21.5, 1.5, 8},
    {15.5, 1.5, 8},
    {16.0, 1.8, 8},
    {16.2, 1.2, 8},
    {3.5,  2.5, 8},
    {9.5, 15.5, 8},
    {10.0, 15.1, 8},
    {10.5, 15.8, 8},
};

int     spritecaster(t_pos *pos)
{
    int spriteOrder[numSprites];
    double spriteDistance[numSprites];
    int i = 0;

    while (i < numSprites)
    {
        spriteOrder[i] = i;
        spriteDistance[i] = ((pos->posX - sprite[i].x) * (pos->posX - sprite[i].x) + (pos->posY - sprite[i].y) * (pos->posY - sprite[i].y));
        i++;
    }
    return (1);

}
