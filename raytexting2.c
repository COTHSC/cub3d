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
	load_image(vars, vars->text[3], "textures/redbrick.xpm");
	load_image(vars, vars->text[4], "textures/redbrick.xpm");
	load_image(vars, vars->text[5], "textures/wood.xpm");
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
    vars.WorldMap = (int **)malloc(sizeof(int *) * 24);
    i = 0;
    while (i <= 24)
    {
        vars.WorldMap[i] = malloc(sizeof(int) * 24);
        i++;
    }

     int Map[24][24] = {
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
          {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3} };

    map_to_struct(Map, &vars);
	mlx_hook(vars.win, 2, 1L << 0, &key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, &key_release, &vars);
	mlx_hook(vars.win, 8, 1L << 5, &button_press, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
