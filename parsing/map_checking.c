/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 09:32:09 by jescully          #+#    #+#             */
/*   Updated: 2021/04/03 12:15:42 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int			inv(t_vars *vars, int n)
{
	if (n != 3 && n != 5 && n != 7 && n != 21 && \
			n != 9 && n != 25 && n != 1 && n != 49)
		exit_game(vars, 1, 5);
	return (1);
}

int			is_end(t_vars *vars, int w, int h)
{
	int		ret;

	ret = 0;
	if (h == 0 || w == (vars->collumn[h] - 1) \
			|| h == (vars->map_h - 1) || w == 0)
	{
		if (get_value(vars, h, w) == 3)
			exit_game(vars, 1, 5);
		if (get_value(vars, h, w) == 7)
			exit_game(vars, 1, 5);
		return (1);
	}
	return (0);
}

void		check_map_ends(t_vars *vars)
{
	int		h;
	int		w;

	h = 0;
	while (++h < (vars->map_h))
	{
		w = 0;
		while (w < vars->collumn[h] && (w < vars->collumn[h - 1] || h == 1))
		{
			if (get_value(vars, h, w) == 3 && w + 1 >= vars->collumn[h - 1])
				exit_game(vars, 1, 5);
			inv(vars, get_value(vars, h, w) * get_value(vars, h - 1, w + 1));
			w++;
		}
	}
	h = -1;
	while (++h < vars->map_h)
	{
		w = 0;
		while (w <= vars->collumn[h])
		{
			is_end(vars, w, h);
			w++;
		}
	}
}

void		check_map2(t_vars *vars)
{
	int		h;
	int		w;

	vars->map[sia(vars->collumn, vars->map_h)] = 5;
	h = 0;
	while (h < (vars->map_h - 1))
	{
		w = 0;
		while (w < vars->collumn[h] - 1 && (w < vars->collumn[h + 1] || h == 0))
		{
			inv(vars, get_value(vars, h, w) * get_value(vars, h, w + 1));
			inv(vars, get_value(vars, h, w) * get_value(vars, h + 1, w));
			inv(vars, get_value(vars, h, w) * get_value(vars, h + 1, w + 1));
			w++;
		}
		h++;
	}
}

void		check_map(t_vars *vars)
{
	int		h;
	int		w;

	check_map_ends(vars);
	h = 1;
	while (h < vars->map_h)
	{
		w = 1;
		while (w < vars->collumn[h] && (w < vars->collumn[h - 1] || h == 1))
		{
			inv(vars, get_value(vars, h, w) * get_value(vars, h - 1, w));
			inv(vars, get_value(vars, h, w) * get_value(vars, h, w - 1));
			inv(vars, get_value(vars, h, w) * get_value(vars, h - 1, w - 1));
			w++;
		}
		h++;
	}
	check_map2(vars);
}
