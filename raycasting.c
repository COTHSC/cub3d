/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:14:27 by jescully          #+#    #+#             */
/*   Updated: 2021/02/15 16:22:15 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

int		init_position(t_vars *vars)
{
	vars->pos->posX = 10;
	vars->pos->posY = 4;
	vars->pos->dirX = -1;
	vars->pos->dirY = 0;
	vars->pos->planeX =  0;
	vars->pos->planeY = 0.66;
	vars->pos->move_speed = 0.05;
	vars->pos->rot_speed = 0.05;
	return (1);
}

int		draw_frame(t_vars *vars)
{

	int w = 640;
	int i = 0;
	int color;

	double cameraX;
	double rayDirX;
	double rayDirY;
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
	int side;
	int lineHeight;
	int h = 480;
	int drawStart;
	int drawEnd;

	vars->img = malloc(sizeof(t_img));
	
	vars->img->ptr = mlx_new_image(vars->mlx, 640, 480);
	vars->img->data = (char *)mlx_get_data_addr(vars->img->ptr, &vars->img->bpp, &vars->img->size_l, &vars->img->endian);
	i = 0;
	printf("this is I %i \n", i);
	while (i++ < w)
	{
		cameraX = (2 * i) / ((double)w - 1);
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
			if (worldMap[mapX][mapY] > 0)
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
		if (drawEnd >= h)
			drawEnd = h -1;
	
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0xA83232;    break; //red
			case 2:  color = 0x40A832;  break; //green
			case 3:  color = 0x326FA8;   break; //blue
			case 4:  color = 0xFFFFFF;  break; //white
			default: color = 0xF5F500; break; //yellow
	      	}
		if (side == 1)
			color = color / 2;

		line_put(vars->img, i, drawStart, drawEnd, color);
	}
	render_next_frame(vars);
	return (1);
}

int             key_hook(int keycode, t_vars *vars)
{  
	double oldDirX;
	double oldPlaneX;

	printf("this is the keycode %i \n", keycode);
    if (keycode == 65362) //linux 65263 right
    {
		if(worldMap[(int)(vars->pos->posX - vars->pos->posY * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
			vars->pos->posX += vars->pos->dirX * vars->pos->move_speed;		
		if(worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY - vars->pos->dirY * vars->pos->move_speed)] == 0)
			vars->pos->posY += vars->pos->dirY * vars->pos->move_speed;
    }
    if (keycode == 65364) // linux 65362 up/front
    {
		if(worldMap[(int)(vars->pos->posX - vars->pos->posY * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
			vars->pos->posX -= vars->pos->dirX * vars->pos->move_speed;
		if(worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY - vars->pos->dirY * vars->pos->move_speed)] == 0)
			vars->pos->posY -= vars->pos->dirY * vars->pos->move_speed;
    }
    if (keycode == 65363) //linux 65364 down/back
    {
		oldDirX = vars->pos->dirX;

		vars->pos->dirX = vars->pos->dirX * cos(-1 * vars->pos->rot_speed) - vars->pos->dirY *sin(-1 * vars->pos->rot_speed);
		vars->pos->dirY = oldDirX * sin(-vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
		oldPlaneX = vars->pos->planeX;	
		vars->pos->planeX = vars->pos->planeX * cos(-1 *(vars->pos->rot_speed)) - vars->pos->planeY * sin(-1 * (vars->pos->rot_speed));
		vars->pos->planeY = oldPlaneX * sin(-1 * vars->pos->rot_speed) + vars->pos->planeY * cos(-1 * vars->pos->rot_speed);
    }
    if (keycode == 65361) //linux 65361 left
    {
		oldDirX = vars->pos->dirX;

		vars->pos->dirX = vars->pos->dirX * cos(vars->pos->rot_speed) - vars->pos->dirY *sin(vars->pos->rot_speed);
		vars->pos->dirY = oldDirX * sin(vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
		oldPlaneX = vars->pos->planeX;	
		vars->pos->planeX = vars->pos->planeX * cos(vars->pos->rot_speed) - vars->pos->planeY * sin(vars->pos->rot_speed);
		vars->pos->planeY = oldPlaneX * sin(vars->pos->rot_speed) + vars->pos->planeY * cos(vars->pos->rot_speed);
    }
    if (keycode == 53)
        mlx_destroy_window(vars->mlx, vars->win);
	
    draw_frame(vars);
    return (1);
}




int main()
{
	t_vars	vars;

	vars.pos = malloc(sizeof(t_pos));
	init_position(&vars);
	
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Hello world!");
	mlx_hook(vars.win, 2, 1L << 0, &key_hook, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
