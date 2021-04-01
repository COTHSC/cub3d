/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:36:54 by jean              #+#    #+#             */
/*   Updated: 2021/04/01 11:07:57 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

int			load_image(t_vars *v, t_img *i, char *path)
{
	i->ptr = mlx_xpm_file_to_image(v->mlx, path, &i->width, &i->height);
	if (i->ptr == NULL)
		return (0);
	i->data = (int *)mlx_get_data_addr(i->ptr, &i->bpp, &i->size_l, &i->endian);
	return (1);
}

int			load_texture(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < 4)
		vars->text[i++] = (t_img *)malloc(sizeof(t_img));
	i = 0;
	i += load_image(vars, vars->text[0], vars->res->SO);
	i += load_image(vars, vars->text[1], vars->res->NO);
	i += load_image(vars, vars->text[2], vars->res->EA);
	i += load_image(vars, vars->text[3], vars->res->WE);
	vars->sprite = (t_img *)malloc(sizeof(t_img));
	i += load_image(vars, vars->sprite, vars->res->S);
	if (i == 5)
	{
		init_sprites(vars);
		return (1);
	}
	exit_game(vars, 2, 6);
	return (0);
}

int			cmp_args(char *str, char *str2)
{
	int		len;
	int		count;

	count = 0;
	len = ft_strlen(str);
	if (!ft_strncmp(&str[len - 4], ".cub", 4))
		count = 1;
	else
		return (0);
	if (ft_strlen(str2) != 0)
	{
		if (!ft_strncmp(str2, "--save", 6) && ft_strlen(str2) == 6)
			count = 2;
		else
			count = 0;
	}
	return (count);
}

void		check_arg(t_vars *vars, int argc, char *arg1, char *arg2)
{
	int		args;

	init_error(vars);
	args = 0;
	vars->save = 0;
	if (argc > 3 || argc == 1)
		exit_game(vars, 0, 0);
	if ((args = cmp_args(arg1, arg2)) == 0)
		exit_game(vars, 0, 0);
	if (args == 2)
		vars->save = 1;
}

int		exit_the_cross(int keycode, t_vars *vars)
{
	exit_game(vars, 0, 7);
	return (1);
}

void		init_to_zero(t_vars *vars)
{
	vars->res->NO = 0;
	vars->res->EA = 0;
	vars->res->SO = 0;
	vars->res->WE = 0;
	vars->res->S = 0;
}

void		init_free_to_zero(t_vars *vars)
{
	vars->to_free->map = 0;
}

int			main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	vars.save = 0;
	vars.to_free = malloc(sizeof(t_needs_freedom));
	init_free_to_zero(&vars);
	check_arg(&vars, argc, argv[1], argv[2]);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		exit_game(&vars, 0, 0);
	vars.keys = malloc(sizeof(t_keys));
	vars.res = malloc(sizeof(t_res));
	init_to_zero(&vars);
	vars.p = malloc(sizeof(t_pos));
	vars.map_h = parse_lines(&vars, fd);
	innit_keys(&vars);
	check_map(&vars);
	vars.mlx = mlx_init();
	check_max_screen_size(&vars);
	load_texture(&vars);
	if (vars.save == 1)
		draw_frame(&vars);
	vars.win = mlx_new_window(vars.mlx, vars.res->w, vars.res->h, "Cub3d");
	mlx_hook(vars.win, 2, 1L << 0, &key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, &key_release, &vars);
	mlx_hook(vars.win, 33, 1L << 17, &exit_the_cross, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
