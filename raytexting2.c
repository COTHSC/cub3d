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
	load_image(vars, vars->text[0], vars->res->EA);
	load_image(vars, vars->text[1], vars->res->WE);
	load_image(vars, vars->text[2], vars->res->SO);
	load_image(vars, vars->text[3], vars->res->NO);
}

void	load_sprites(t_vars *vars)
{
	load_image(vars, vars->sprite, vars->res->S);
}

int main(int argc, char **argv)
{
	t_vars	vars;
	int i = 0;
    int fd;  

    fd = open(argv[1], O_RDONLY);
    vars.res = malloc(sizeof(t_res));
    vars.p = malloc(sizeof(t_pos));
    vars.map_h = parse_lines(&vars, fd);
    if(check_map(&vars) == -1)
    {
        printf("Error, Map in invalid \n");
        return 0;
    }
	vars.keys = malloc(sizeof(t_keys));
	innit_keys(&vars);
	while (i < 4)
		vars.text[i++] = (t_img *)malloc(sizeof(t_img));
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.res->w, vars.res->h, "Hello world!");
	load_texture(&vars);

    i = 0;
    vars.buf = malloc(sizeof(int *) * vars.res->h);
    while (i < vars.res->h)
        vars.buf[i++] = malloc(sizeof(int) * vars.res->w);
    vars.sprite = (t_img *)malloc(sizeof(t_img));
	load_sprites(&vars);
    init_sprites(&vars);
	mlx_hook(vars.win, 2, 1L << 0, &key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, &key_release, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
