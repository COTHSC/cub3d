/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:14:27 by jescully          #+#    #+#             */
/*   Updated: 2021/02/16 11:17:10 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     worldMap[mapWidth][mapHeight] =
{
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
        {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
        {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
        {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
        {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
        {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
        {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
        {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
        {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
        {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
        {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
        {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
        {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
        {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
        {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
        {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
        {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
        {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
        {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
        {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
        {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};



int		init_position(t_vars *vars)
{
	vars->pos->posX = 22.0;
	vars->pos->posY = 11.5;
	vars->pos->dirX = -1;
	vars->pos->dirY = 0;
	vars->pos->planeX =  0;
	vars->pos->planeY = 0.66;
	vars->pos->move_speed = 0.03;
	vars->pos->rot_speed = 0.03;
	return (1);
}

void	draw(t_vars *vars)
{

	for (int y = 0; y < 480; y++)
	{
		for (int x = 0; x < 640; x++)
			vars->img->data[y * 640 + x] = vars->buf[y][x];
	}

	reset_buffer(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	free(vars->img);
}

int		draw_frame(t_vars *vars)
{

	int w = 640;
	int i = 0;
	int color;

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
	int h = 480;
	int y;
	int drawStart;
	int drawEnd;
	int texNum;

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
		if (drawEnd >= h || drawEnd < 0)
			drawEnd = h - 1;

		if (side == 0)
			wallX = vars->pos->posY + perpWallDist * rayDirY;
		else
			wallX = vars->pos->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		texNum = worldMap[mapX][mapY] - 1;

		texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX -1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX -1;
		if (side == 1)
			color = color / 2;
		step = 1.0 * texHeight / lineHeight;
		texPos = (drawStart - (h / 2) + (lineHeight / 2)) * step;
		y = drawStart;
		texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		while (y < drawEnd)
		{
			texY = (int)texPos & (texHeight -1);
			texPos += step;
			color = vars->text[texNum]->data[texWidth * texY + texX]; 
			vars->buf[y][i] = color;	
			y++;
		}
		draw_cieling(vars, i, drawStart);
		draw_floor(vars, i, drawEnd);
		i++;
	}
	draw(vars);
	return (1);
}

int             key_hook(t_vars *vars)
{  
	double oldDirX;
	double oldPlaneX;

	if (vars->keys->w) 
	{
		if(worldMap[(int)(vars->pos->posX + vars->pos->dirX * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
			vars->pos->posX += vars->pos->dirX * vars->pos->move_speed;		
		if(worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY + vars->pos->dirY * vars->pos->move_speed)] == 0)
			vars->pos->posY += vars->pos->dirY * vars->pos->move_speed;
	}
	if (vars->keys->s)
	{
		if(worldMap[(int)(vars->pos->posX - vars->pos->dirX * vars->pos->move_speed)][(int)(vars->pos->posY)] == 0)
			vars->pos->posX -= vars->pos->dirX * vars->pos->move_speed;
		if(worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY - vars->pos->dirY * vars->pos->move_speed)] == 0)
			vars->pos->posY -= vars->pos->dirY * vars->pos->move_speed;
	}
	if (vars->keys->r)
	{
		oldDirX = vars->pos->dirX;

		vars->pos->dirX = vars->pos->dirX * cos(-1 * vars->pos->rot_speed) - vars->pos->dirY *sin(-1 * vars->pos->rot_speed);
		vars->pos->dirY = oldDirX * sin(-vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
		oldPlaneX = vars->pos->planeX;	
		vars->pos->planeX = vars->pos->planeX * cos(-1 *(vars->pos->rot_speed)) - vars->pos->planeY * sin(-1 * (vars->pos->rot_speed));
		vars->pos->planeY = oldPlaneX * sin(-1 * vars->pos->rot_speed) + vars->pos->planeY * cos(-1 * vars->pos->rot_speed);
	}
	if (vars->keys->l)
	{
		oldDirX = vars->pos->dirX;

		vars->pos->dirX = vars->pos->dirX * cos(vars->pos->rot_speed) - vars->pos->dirY *sin(vars->pos->rot_speed);
		vars->pos->dirY = oldDirX * sin(vars->pos->rot_speed) + vars->pos->dirY * cos(-vars->pos->rot_speed);
		oldPlaneX = vars->pos->planeX;	
		vars->pos->planeX = vars->pos->planeX * cos(vars->pos->rot_speed) - vars->pos->planeY * sin(vars->pos->rot_speed);
		vars->pos->planeY = oldPlaneX * sin(vars->pos->rot_speed) + vars->pos->planeY * cos(vars->pos->rot_speed);
	}
	draw_frame(vars);
	return (1);
}

void	load_image(t_vars *vars, t_img *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(vars->mlx, path, &img->width, &img->height);
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp, &img->size_l, &img->endian);
}

void	load_texture(t_vars *vars)
{
	load_image(vars, vars->text[0], "textures/eagle.xpm");
	load_image(vars, vars->text[1], "textures/redbrick.xpm");
	load_image(vars, vars->text[2], "textures/purplestone.xpm");
	load_image(vars, vars->text[3], "textures/greystone.xpm");
	load_image(vars, vars->text[4], "textures/bluestone.xpm");
	load_image(vars, vars->text[5], "textures/mossy.xpm");
	load_image(vars, vars->text[6], "textures/wood.xpm");
	load_image(vars, vars->text[7], "textures/colorstone.xpm");
}

int main()
{
	t_vars	vars;
	int i = 0;

	vars.pos = malloc(sizeof(t_pos));
	vars.keys = malloc(sizeof(t_keys));
	init_position(&vars);
	while (i < 8)
		vars.text[i++] = (t_img *)malloc(sizeof(t_img));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, screenWidth, screenHeight, "Hello world!");
	load_texture(&vars);
	mlx_hook(vars.win, 2, 1L << 0, &key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, &key_release, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
