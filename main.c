/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 14:14:27 by jescully          #+#    #+#             */
/*   Updated: 2021/03/17 12:27:54 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int		load_image(t_vars *vars, t_img *img, char *path)
{

	img->ptr = mlx_xpm_file_to_image(vars->mlx, path, &img->width, &img->height);
	if (img->ptr == NULL)
		return (0);
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bpp, &img->size_l, &img->endian);
	return (1);
}

int		load_texture (t_vars *vars)
{
	int i;

	i = 0;
	i += load_image(vars, vars->text[0], vars->res->SO);
	i += load_image(vars, vars->text[1], vars->res->NO);
	i += load_image(vars, vars->text[2], vars->res->EA);
	i += load_image(vars, vars->text[3], vars->res->WE);
	if (i == 4)
		return (1);
	return (0);
}

void	load_sprites(t_vars *vars)
{
	load_image(vars, vars->sprite, vars->res->S);
}

int check_arg(char *str, char *str2)
{
	int 	len;
	int		count;

	count = 0;
	if (!str)
		printf("Error\nPlease enter an arg");
	len = ft_strlen(str);
	if (!ft_strncmp(&str[len - 4], ".cub", 4))
	{
		count++;
	}

	if (ft_strlen(str2) != 0)
	{
		if (!ft_strncmp(str2, "--save", 6) && ft_strlen(str2) == 6)
			count++;
		else
			count--;
	}
	return (count);
}

int main(int argc, char **argv)
{
	t_vars	vars;
	int i = 0;
    int fd;
    int args;

    vars.save = 0;
    if ( argc > 3 || argc == 1)
	{
		printf("Error\nInvalid Arg");
		exit_game(&vars, 0);
    }
    if ((args = check_arg(argv[1], argv[2])) == 0)
	{
		printf("Error\nInvalid Arg");
		exit_game(&vars, 0);
    }
    if (args == 2)
        vars.save = 1;
    fd = open(argv[1], O_RDONLY);
    //from here its another ballgame of freeing stuff
    
    vars.res = malloc(sizeof(t_res));
    vars.p = malloc(sizeof(t_pos));
    vars.map_h = parse_lines(&vars, fd);
   // this is free it post past lines from here all is to be freed 


	vars.keys = malloc(sizeof(t_keys));
	innit_keys(&vars);
	while (i < 4)
		vars.text[i++] = (t_img *)malloc(sizeof(t_img));
    if(check_map(&vars) == -1)
   	{
       printf("Error\n Map in invalid \n");
       exit_game(&vars, 1);
       return 0;
  	}
	vars.mlx = mlx_init();
	if (!load_texture(&vars))
	{		
        printf("Error\n textures invalid \n");
		exit_game(&vars, 2);
	}
    i = 0;
    vars.buf = malloc(sizeof(int *) * vars.res->h);
    while (i < vars.res->h)
        vars.buf[i++] = malloc(sizeof(int) * vars.res->w);
    vars.sprite = (t_img *)malloc(sizeof(t_img));
	load_sprites(&vars);
    init_sprites(&vars);

    if (vars.save != 1)
    {
    	vars.win = mlx_new_window(vars.mlx, vars.res->w, vars.res->h, "Cub3d");
    }
    else
    {
        draw_frame(&vars);
    } 
	mlx_hook(vars.win, 2, 1L << 0, &key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, &key_release, &vars);
	mlx_hook(vars.win, 33, 1L << 17, &exit_game, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	mlx_loop(vars.mlx);
	return 0;
}
