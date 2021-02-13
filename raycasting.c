/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycsting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:14:27 by jescully          #+#    #+#             */
/*   Updated: 2021/02/11 16:27:07 by jescully         ###   ########.fr       */
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
	int         *data;
	int         width;
	int         height;

	int         bpp;
	int         size_l;
	int         endian;
}               t_img;

typedef struct  s_pos {
	int        	y;
	int			x;
	float		angle;
	float		cos;
	float		sin;

}       		t_pos;

typedef struct  s_vars {
	void        *mlx;
	void        *win;
	t_pos		*position;
	int 		*data;
	void 		*img;
	void		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}               t_vars;

void            my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	int *dst;
	dst = img->data + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void			my_mlx_line_put(t_img *img, int x, int start, int end, int color)
{
	int i;

	i = start;
	while (i++ < end)
		img->data[i * 640 + x] = color;
	//my_mlx_pixel_put(img, x, start, color);
}	


//place the example code below here:

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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


int main()
{
	double posX = 10;
	double dirX = -1;
	double posY = 21;
	double dirY = 0;
	double planeY = 0.66;
	double planeX = 0;
	int w = 640;
	int i = 0;
	int color;

	double cameraX;
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	t_vars	vars;
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
	t_img *img;

	img = malloc(sizeof(t_img));

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Hello world!");
	img->ptr = mlx_new_image(vars.mlx, 640, 480);
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp, &img->size_l, &img->endian);
//	mlx_put_image_to_window(vars.mlx, vars.win, img.ptr,0,0);
	while (i++ < w)
	{
		cameraX = 2 * i / w - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;

		mapX = (int)posX;
		mapY = (int)posY;

		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);

		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) *deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) *deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) *deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) *deltaDistY;
		}
		
		hit = 0;

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
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(h / perpWallDist);


		drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >=h)
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
			printf("side = 1 \n");
			color = color / 2;
		}
	my_mlx_line_put(img, i, drawStart, drawEnd, color);


	}

	printf("this is me out of the loop. \n", i);
	mlx_put_image_to_window(vars.mlx, vars.win, img->ptr,0,0);

	mlx_loop(vars.mlx);
	return 0;
}
