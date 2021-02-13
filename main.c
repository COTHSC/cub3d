/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 07:14:36 by jescully          #+#    #+#             */
/*   Updated: 2021/02/12 15:53:36 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_linux/mlx.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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




int		init_struct(t_vars *vars)
{
	if (!(vars->position = malloc(sizeof(t_pos*))))
		return 0;
	vars->position->y = 300;
	vars->position->x = 0;
	vars->position->angle = 0;
	vars->position->cos = 0;
	vars->position->sin = 0;
	return 1;
}
/*
void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
*/
int             key_hook(int keycode, t_vars *vars)
{ 	int i = 0;
	int h = -1;
	int w = -1;
	int *img_height;
	int *img_width;

	if (keycode == 65363)
	{
		vars->position->angle += 1.5708;
		if (vars->position->angle > 6.283)
			vars->position->angle = 0;
		printf("the angle is %f \n", vars->position->angle);
		vars->position->cos = cos(vars->position->angle);
		vars->position->sin = sin(vars->position->angle);
		//		printf("the cos is %f \n", vars->position->cos);
	}
	if (keycode == 65362)
	{
		vars->position->x += 10 * vars->position->cos;
		if (vars->position->y > 600)
			vars->position->y = 0;
		vars->position->y += 10 * vars->position->sin;
		if (vars->position->y > 600)
			vars->position->y = 0;
		//		printf("the sin is now is %f \n", vars->position->sin);
	}
	if (keycode == 65364)
	{
		vars->position->x -= 10 * vars->position->cos;
		if (vars->position->x > 600)
			vars->position->x = 0;
		vars->position->y -= 10 * vars->position->sin;
		if (vars->position->y > 600)
			vars->position->y = 0;
		//		printf("the x now is %i \n", vars->position->x);
	}
	if (keycode == 65361)
	{
		vars->position->angle -= 1.5708;
		if (vars->position->angle > 6.283)
			vars->position->angle = 0;
		vars->position->cos = cos(vars->position->angle);
		vars->position->sin = sin(vars->position->angle);
		printf("the angle i %f \n", vars->position->angle);
		printf("the cos is %f \n", vars->position->cos);
	}
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
}


int     render_next_frame(t_vars *vars)
{
	int h = -1;
	int w = -1;
	int img_height;
	int img_width;
	void *imgt;
	void *imgt2;
	int times = 50;
	int move;

	imgt2 = mlx_new_image(vars->mlx, 640, 480);
	mlx_put_image_to_window(vars->mlx, vars->win, imgt2, 0, 0);
	mlx_destroy_image(vars->mlx, imgt2);
	imgt = mlx_xpm_file_to_image(vars->mlx, "./pacman/pacman.xpm", &img_width, &img_height);
	move += img_width;
	mlx_put_image_to_window(vars->mlx, vars->win, imgt, vars->position->x , vars->position->y);
	mlx_destroy_image(vars->mlx, imgt);

}

int             main(void)
{
	int H = 480;
	int L = 640;
	t_img	img;
	t_vars      vars;
	int i=0;

	int img_width;
	int img_height;


	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, L, H, "Hello world!");
	init_struct(&vars);
	mlx_hook(vars.win, 2, 1L << 0, &key_hook, &vars);
	//	vars.img = mlx_xpm_file_to_image(vars.mlx, "./pacman/pacman.xpm", &img_width, &img_height);
	//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//	my_mlx_pixel_put(&img, vars.position->x, vars.position->y, 111);
	printf("these are the values of x %i and y %i \n", vars.position->x, vars.position->y);
	//	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, vars.position->x, vars.position->y);
	printf("this is i %i\n", i);
	mlx_loop_hook(vars.mlx, &render_next_frame, &vars);

	mlx_loop(vars.mlx);
} 

/*int main()
  {
  int H = 600;
  int L = 600;
  int offset;
  t_data	img;
  t_vars vars;
  vars.mlx = mlx_init();
  vars.win = mlx_new_window(vars.mlx, H, L, "test window");
  img.img = mlx_new_image(vars.mlx, H, L);
  img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//	offset =  (L * img.line_length + H * (img.bits_per_pixel/8));
my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
mlx_put_image_to_window(vars.win, vars.mlx, img.img, 0, 0);
//	add_line(mlx_ptr, win_ptr);
mlx_loop(vars.mlx);
return 0;
}*/
