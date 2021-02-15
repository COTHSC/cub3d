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


#include <math.h>
//#include <mlx.h>
#include "mlx_linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
/*
   g++ *.cpp -lSDL -O3 -W -Wall -ansi -pedantic
   g++ *.cpp -lSDL
   */

typedef struct  s_img {
	void        *ptr;
	char        *data;
	int         width;
	int         height;

	int         bpp;
	int         size_l;
	int         endian;
}               t_img;

typedef struct  s_pos {
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double 		move_speed;
	double 		rot_speed;
}       		t_pos;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	t_pos		*pos;
	t_img		*img;
}               t_vars;

void            my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int *dst;
	printf("this is size_l %i\n", img->size_l);
	dst = img->data + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void		pixel_put(t_img *image, int x, int y, int color)
{
	unsigned char *src;
	unsigned char r;
	unsigned char g;
	unsigned char b;

	src = (unsigned char *)&color;
	r = src[0];
	g = src[1];
	b = src[2];
	image->data[y * image->size_l + x * image->bpp / 8] = r;
	image->data[y * image->size_l + x * image->bpp / 8 + 1] = g;
	image->data[y * image->size_l + x * image->bpp / 8 + 2] = b;
}

void			my_mlx_line_put(t_img *img, int x, int start, int end, int color)
{
	int i;

	//printf("this is size_l %i\n", img->size_l);
	i = start;
	while (i++ < end)
		pixel_put(img, x, i, color);
//		img->data[i * 640 + x] = color;
//	my_mlx_pixel_put(img, x, start, color);
}	


int     render_next_frame(t_vars *vars)
{
    void *imgt2;

    imgt2 = mlx_new_image(vars->mlx, 640, 480);
    mlx_put_image_to_window(vars->mlx, vars->win, imgt2, 0, 0);
	mlx_destroy_image(vars->mlx, imgt2);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->ptr, vars->pos->posX, vars->pos->posY);
 	mlx_destroy_image(vars->mlx, vars->img->ptr);
}
//place the example code below here:

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
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	vars->pos->move_speed = 0.5;
	vars->pos->rot_speed = 0.005;
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
	vars->img->data = (int *)mlx_get_data_addr(vars->img->ptr, &vars->img->bpp, &vars->img->size_l, &vars->img->endian);
	i = 0;
	printf("this is I %i \n", i);
	while (i++ < w)
	{
		cameraX = 2 * i / w - 1;
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
		

	//	printf("this is mapX %i \n", mapX);
	//	printf("this is mapY %i \n", mapY);
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
		lineHeight = 0;
			perpWallDist = (mapY - vars->pos->posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(h / perpWallDist);
		
	//	printf("this is posX %f \n", vars->pos->posX);
	//	printf("this is posY %f \n", vars->pos->posY);
		printf("this is stepX %i \n", stepX);
		printf("this is stepY %i \n", stepY);
//		printf("this is stepX %i \n", stepX);
//		printf("this is stepY %i \n", stepY);
//		printf("this is line height %i \n", lineHeight);
		printf("this is perpwalldist %f \n", perpWallDist);
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
		{
//			printf("side = 1 \n");
			color = color / 2;
		}

		my_mlx_line_put(vars->img, i, drawStart, drawEnd, color);
	}
	printf("this is I %i \n", i);
	render_next_frame(vars);
//	printf("kilroy was here \n");

}

int             key_hook(int keycode, t_vars *vars)
{  
	double oldDirX;
	double oldDirY;
	double oldPlaneX;
	double oldPlaneY;

	printf("im in the key hook now\n");
    if (keycode == 126) //linux 65263 right
    {
		if(worldMap[(int)(vars->pos->posX - vars->pos->posY * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
			vars->pos->posX += vars->pos->dirX * vars->pos->move_speed;
    }
    if (keycode == 125) // linux 65362 up/front
    {
		if(worldMap[(int)(vars->pos->posX - vars->pos->posY * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
			vars->pos->posX -= vars->pos->dirX * vars->pos->move_speed;
    }
    if (keycode == 124) //linux 65364 down/back
    {
		oldDirX = vars->pos->dirX;

		vars->pos->dirX = vars->pos->dirX * cos(-1 * vars->pos->rot_speed) - vars->pos->dirY *sin(-1 * vars->pos->rot_speed);
		vars->pos->dirY = oldDirX * sin(-vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
		oldPlaneX = vars->pos->planeX;	
		vars->pos->planeX = vars->pos->planeX * cos(-1 *(vars->pos->rot_speed)) - vars->pos->planeY * sin(-1 * (vars->pos->rot_speed));
		vars->pos->planeY = oldPlaneX * sin(-1 * vars->pos->rot_speed) + vars->pos->planeY * cos(-1 * vars->pos->rot_speed);
    }
    if (keycode == 123) //linux 65361 left
    {
		oldDirX = vars->pos->dirX;

		vars->pos->dirX = vars->pos->dirX * cos(vars->pos->rot_speed) - vars->pos->dirY *sin(vars->pos->rot_speed);
		vars->pos->dirY = oldDirX * sin(-vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
		oldPlaneX = vars->pos->planeX;	
		vars->pos->planeX = vars->pos->planeX * cos(vars->pos->rot_speed) - vars->pos->planeY * sin(vars->pos->rot_speed);
		vars->pos->planeY = oldPlaneX * sin(vars->pos->rot_speed) + vars->pos->planeY * cos(vars->pos->rot_speed);
    }
    if (keycode == 53)
        mlx_destroy_window(vars->mlx, vars->win);
	printf("this is my position x: %f and y: %f \n", vars->pos->posX, vars->pos->posY);
	draw_frame(vars);
//	render_next_frame(vars);
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
