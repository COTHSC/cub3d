/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 07:14:36 by jescully          #+#    #+#             */
/*   Updated: 2021/02/10 16:18:17 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_img {
	void 		*ptr;
	int			*data;
	int			width;
	int			height;

	int			bpp;
	int			size_l;
	int			endian;
}				t_img;

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
	t_img		imgdata;
	t_img	*buffdata;
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

int     render_next_frame(t_vars *vars )
{
	int h = -1;
	int w = -1;
	int img_height;
	int img_width;
	t_img img;
	void *imgt;
	void *imgt2;
	int times = 50;
	int move;

move = 0;
	while (times++ < 60)
	{

		imgt2 = mlx_new_image(vars->mlx, 1920, 1080);
		mlx_put_image_to_window(vars->mlx, vars->win, imgt2,0,0);
		mlx_destroy_image(vars->mlx, imgt2);
		imgt = mlx_xpm_file_to_image(vars->mlx, "./pacman/pacman.xpm", &img_width, &img_height);
		printf("this is img_witdth %d \n", img_width);
		move += img_width;
		mlx_put_image_to_window(vars->mlx, vars->win, imgt, move , 50);
		mlx_destroy_image(vars->mlx, imgt);

	}
}


int             main(void)
{
	int H = 1080;
	int L = 1920;
	t_img	img;
	t_vars      vars;
	int i=0;

	int img_width;
	int img_height;


	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, L, H, "Hello world!");
	init_struct(&vars);
	//	mlx_hook(vars.win, 2, 0, &key_hook, &vars);
	//	vars.img = mlx_xpm_file_to_image(vars.mlx, "./pacman/pacman.xpm", &img_width, &img_height);
	//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//	my_mlx_pixel_put(&img, vars.position->x, vars.position->y, 111);
	//	printf("these are the values of x %i and y %i \n", vars.position->x, vars.position->y);
	//	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, vars.position->x, vars.position->y);
	//	printf("this is i %i\n", i);
	mlx_loop_hook(vars.mlx, &render_next_frame, &vars);
	mlx_loop(vars.mlx);
} 
