#include "../cub3d.h"

#define numSprites 8

int     innit_sprites(t_sprites **sprite, double x, double y, int num)
{
    sprite[num]->x = x;
    sprite[num]->y = y;
    sprite[num]->texture = 1;
    sprite[num]->dist = 0;
    return (1);
}

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
    i = 0;
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
        transformY = invDet * (vars->pos->planeY * spriteX - vars->pos->planeX * spriteY);
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
            texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * 256 / spriteWidth) / 256;
            if(transformY > 0 && stripe > 0 && stripe < w && transformY < zbuffer[stripe])
                for(int y = drawStartY; y < drawEndY; y++)
                {
                    int d = (y) * 256 - h * 128 + spriteHeight * 128;
                    texY = ((d * 64) / spriteHeight) / 256;
                    color = vars->text[sprite[i]->texture]->data[64 * texY + texX]; 
                    if((color & 0x00FFFFFF) != 0) vars->buf[y][stripe] = color; 
                }
        }
        i++;
    }
    return (1);

}



int		draw_frame(t_vars *vars)
{
    int w = screenWidth;
    int i = 0;
    int color;
    int zbuffer[screenWidth];
    double cameraX;
    double rayDirX;
    double rayDirY;
    double wallX;
    double step;
    double texPos;
    int texX;
    int texY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit = 0;
    int side = 0;
    int lineHeight;
    int h = screenHeight;
    int y;
    int drawStart;
    int drawEnd;
    int texNum = 0;

    vars->img = malloc(sizeof(t_img));

    vars->img->ptr = mlx_new_image(vars->mlx, screenWidth, screenHeight );
    vars->img->data = (int *)mlx_get_data_addr(vars->img->ptr, &vars->img->bpp, &vars->img->size_l, &vars->img->endian);
    i = 0;
    while (i < w - 1)
    {
        cameraX = (2 * i) / ((double)w) - 1;
        rayDirX = vars->pos->dirX + vars->pos->planeX * cameraX;
        rayDirY = vars->pos->dirY + vars->pos->planeY * cameraX;

        mapX = (int)vars->pos->posX;
        mapY = (int)vars->pos->posY;

        deltaDistX = fabs(1 / rayDirX);
        deltaDistY = fabs(1 / rayDirY);
        hit = 0;

        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (vars->pos->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - vars->pos->posX) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (vars->pos->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - vars->pos->posY) * deltaDistY;
        }

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (vars->WorldMap[mapX][mapY] > 0)
                hit = 1;
        }
        if (side == 0)
            perpWallDist = (mapX - vars->pos->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - vars->pos->posY + (1 - stepY) / 2) / rayDirY;
        lineHeight = (int)(h / perpWallDist);
        drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h || drawEnd < 0)
            drawEnd = h - 1;

        if (side == 0)
            wallX = vars->pos->posY + perpWallDist * rayDirY;
        else
            wallX = vars->pos->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        texNum = vars->WorldMap[mapX][mapY] - 1;

        texX = (int)(wallX * (double)vars->text[texNum]->width);
        if (side == 0 && rayDirX > 0)
            texX = vars->text[texNum]->width - texX -1;
        if (side == 1 && rayDirY < 0)
            texX = vars->text[texNum]->width - texX -1;
        step = 1.0 * vars->text[texNum]->height / lineHeight;
        texPos = (drawStart - (h / 2) + (lineHeight / 2)) * step;
        y = drawStart;
        while (y < drawEnd)
        {
            texY = (int)texPos & (vars->text[texNum]->height -1);
            texPos += step;
            color = vars->text[texNum]->data[vars->text[texNum]->width * texY + texX];
            vars->buf[y][i] = color;
            y++;
        }
        draw_cieling(vars, i, drawStart);
        draw_floor(vars, i, drawEnd);
        zbuffer[i] = perpWallDist;
        i++;
    }
    spritecaster(vars, texX, texY, texNum, zbuffer);
    draw(vars);
    return (1);
}

