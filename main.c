/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:36:54 by jean              #+#    #+#             */
/*   Updated: 2021/04/02 11:20:54 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft/libft.h"

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

int			check_arg(t_vars *vars, int argc, char *arg1, char *arg2)
{
	int		args;
	int		fd;

	init_error(vars);
	args = 0;
	vars->save = 0;
	if (argc > 3 || argc == 1)
		exit_game(vars, 0, 0);
	if ((args = cmp_args(arg1, arg2)) == 0)
		exit_game(vars, 0, 0);
	if (args == 2)
		vars->save = 1;
	if ((fd = open(arg1, O_RDONLY)) == -1)
		exit_game(vars, 0, 0);
	return (fd);
}

void		just_mallocs(t_vars vars)
{
	vars.keys = malloc(sizeof(t_keys));
	vars.res = malloc(sizeof(t_res));
	init_to_zero(&vars);
	vars.p = malloc(sizeof(t_pos));
}

int			main(int argc, char **argv)
{
	t_vars	vars;
	int		fd;

	vars.save = 0;
	vars.to_free = malloc(sizeof(t_needs_freedom));
	init_free_to_zero(&vars);
	fd = check_arg(&vars, argc, argv[1], argv[2]);
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
	vars.win = mlx_new_window(vars.mlx, vars.res->w, vars.res->h, "Cub3d");
	mlx_hook(vars.win, 2, 1L << 0, &key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, &key_release, &vars);
	mlx_hook(vars.win, 33, 1L << 17, &exit_the_cross, &vars);
	mlx_loop_hook(vars.mlx, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
