#include "../cub3d.h"



int		draw_frame(t_vars *vars)
{
    int w = vars->res->w;
    int i = 0;
    int color;
    int *zbuffer;
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
    int h = vars->res->h;
    int y;
    int drawStart;
    int drawEnd;
    int texNum = 0;

    zbuffer = malloc(sizeof(int) * w);
    vars->img = malloc(sizeof(t_img));

    vars->img->ptr = mlx_new_image(vars->mlx, vars->res->w, vars->res->h );
    vars->img->data = (int *)mlx_get_data_addr(vars->img->ptr, &vars->img->bpp, &vars->img->size_l, &vars->img->endian);
    i = 0;
    while (i < w - 1)
    {
        cameraX = (2 * i) / ((double)w) - 1;
        rayDirX = vars->p->dx + vars->p->plx * cameraX;
        rayDirY = vars->p->dy + vars->p->ply * cameraX;

        mapX = (int)vars->p->px;
        mapY = (int)vars->p->py;

        deltaDistX = fabs(1 / rayDirX);
        deltaDistY = fabs(1 / rayDirY);
        hit = 0;

        if(rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (vars->p->px - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - vars->p->px) * deltaDistX;
        }
        if(rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (vars->p->py - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - vars->p->py) * deltaDistY;
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
            if (*(vars->map + sia(vars->collumn, mapX) + mapY) == 1)
                hit = 1;
        }
        if (side == 0)
            perpWallDist = (mapX - vars->p->px + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - vars->p->py + (1 - stepY) / 2) / rayDirY;
        lineHeight = (int)(h / perpWallDist);
        drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0)
            drawStart = 0;
        drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h || drawEnd < 0)
            drawEnd = h - 1;
        if (side == 0)
            wallX = vars->p->py + perpWallDist * rayDirY;
        else
            wallX = vars->p->px + perpWallDist * rayDirX;
        wallX -= floor(wallX);
        if (side == 0 && rayDirX >=0 )
            texNum = 0;
        else if (side == 0 && rayDirX < 0)
            texNum = 1;
        else if (side == 1 && rayDirY >= 0)
            texNum = 2;
        else 
            texNum = 3;
        texX = (int)(wallX * (double)vars->text[texNum]->width);
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
    spritecaster(vars, texX, texY, zbuffer);
    free(zbuffer);
    draw(vars);
    return (1);
}

