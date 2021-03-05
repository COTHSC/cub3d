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

void	load_texture (t_vars *vars)
{
	load_image(vars, vars->text[0], "textures/eagle.xpm");
	load_image(vars, vars->text[1], "textures/purplestone.xpm");
	load_image(vars, vars->text[2], "textures/colorstone.xpm");
	load_image(vars, vars->text[3], "textures/mossy.xpm");
}

void	load_sprites(t_vars *vars)
{
	load_image(vars, vars->sprite, "textures/barrel.xpm");
}

int main(int argc, char **argv)
{
	t_vars	vars;
	int i = 0;
    int fd;  

    fd = open(argv[1], O_RDONLY);
    vars.res = malloc(sizeof(t_res));
    vars.p = malloc(sizeof(t_pos));
    parse_lines(&vars, fd);
    printf("this is the path: %s \n", vars.res->NO);
    printf("this is the path: %s \n", vars.res->SO);
    printf("this is the path: %s \n", vars.res->WE);
    printf("this is the path: %s \n", vars.res->EA);
    printf("this is the path: %s \n", vars.res->S);
    printf("this is the color: %X \n", vars.res->C);
    printf("this is the color: %X \n", vars.res->F);
	

	vars.keys = malloc(sizeof(t_keys));
	innit_keys(&vars);
    //init_position(&vars);
	while (i < 8)
		vars.text[i++] = (t_img *)malloc(sizeof(t_img));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.res->w, vars.res->h, "Hello world!");
	load_texture(&vars);

    i = 0;
    vars.buf = malloc(sizeof(int *) * vars.res->h);
    while (i < vars.res->h)
    {
        vars.buf[i] = malloc(sizeof(int) * vars.res->w);
        i++;
    }
    vars.sprite = (t_img *)malloc(sizeof(t_img));
	load_sprites(&vars);

    vars.WorldMap = (int **)malloc(sizeof(int *) * 24);
    i = 0;
    while (i <= 24)
    {
        vars.WorldMap[i] = malloc(sizeof(int) * 24);
        i++;
    }

     int Map[24][24] = {
          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

    i = 0;
    int j;
    while(i < 24)
    {
        j = 0;
        while(j < vars.collumn[i])
        {
            printf("%i ", *(vars.map + sia(vars.collumn, i)  + j));
            j++;
        }
        printf("\n");
        i++;
    }

	//return 0;
    map_to_struct(vars.map, &vars);
	mlx_hook(vars.win, 2, 1L << 0, &key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, &key_release, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
