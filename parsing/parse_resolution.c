/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:23:04 by jescully          #+#    #+#             */
/*   Updated: 2021/03/31 11:48:51 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

void		i_through_space(char *str, int *i)
{
	int j;

	j = *i;
	while (ft_isspace(str[j]))
		j++;
	*i = j;
}

void		direct_function(t_vars *vars, fptr functions[8], char *buf)
{
	int		c;
	int		j;

	j = 0;
	c = 0;
	i_through_space(buf, &j);
	while (c < 8)
	{
		if (!empty_line(buf))
			++vars->res->count;
		if (!ft_strncmp(&buf[j], vars->farray[c], ft_strlen(vars->farray[c])))
		{
			if (!(*functions[c])(vars->res, &buf[j]))
				exit_game(vars, 1, 3);
		}
		c++;
	}
}

int			parse_lines(t_vars *vars, int fd)
{
	char	*buf;
	int		h;
	fptr	functions[8];

	h = 0;
	vars->res->count = 0;
	vars->farray = malloc(sizeof(char *) * 8);
	innit_arrayf(functions, vars);
    vars->to_free->farray++;
	while (get_next_line(fd, &buf) != 0)
	{
		direct_function(vars, functions, buf);
		if (check_struct(vars->res))
		{
			h = parse_map(vars, fd);
			free(buf);
			return (h);
		}
		free(buf);
	}
	exit_game(vars, 1, 1);
	return (0);
}

int			parse_colors(t_res *res, char *buf)
{
	int		r;
	int		g;
	int		b;
	int		i;
	int		color;

	i = -1;
	color = 0;
	while (!ft_isdigit(buf[++i]))
		if (!ft_isspace(buf[i]) && buf[i] != 'F' && buf[i] != 'C')
			return (0);
	r = ft_atoi(&buf[i]);
	while (buf[i] != ',')
	{
		if (!ft_isdigit(buf[i]) && !ft_isspace(buf[i]))
			return (0);
		i++;
	}
	g = ft_atoi(&buf[i + 1]);
	while (buf[++i] != ',')
		if (!ft_isdigit(buf[i]) && !ft_isspace(buf[i]))
			return (0);
	if (!ft_isdigit(buf[i + 1]))
		return (0);
	b = ft_atoi(&buf[++i]);
	while (ft_isdigit(buf[i]))
		i++;
	i -= 1;
	while (buf[++i] && buf[i] != '\n')
		if (!ft_isspace(buf[i]))
			return (0);
	if (r > 255 || g > 255 || b > 255)
		return (0);
	color = ft_get_color(r, g, b);
	if (ft_strnstr(buf, "F ", 2))
		res->F = color;
	else if (ft_strnstr(buf, "C ", 2))
		res->C = color;
	return (1);
}

int			parse_resolution(t_res *res, char *buf)
{
	int		i;

	i = -1;
	while (!ft_isdigit(buf[++i]))
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != 'R')
			return (0);
	res->w = ft_atoi(&buf[i]);
	while (ft_isdigit(buf[i]))
		i++;
	while (!ft_isdigit(buf[i]) && buf[i])
	{
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != 'R')
			return (0);
		i++;
	}
	res->h = ft_atoi(&buf[i]);
	while (ft_isdigit(buf[i]))
		i++;
	i -= 1;
	while (buf[++i] && buf[i] != '\n')
		if (!ft_isspace(buf[i]))
			return (0);
	return (1);
}

int			parse_paths(t_res *res, char *buf)
{
	int		i;
	int		length;
	int		start;

	if (!buf)
		return (0);
	i = 0;
	length = 0;
	while (buf[i] != ' ')
		i++;
	while (buf[i] == ' ')
		i++;
	start = i;
	while (buf[i] && buf[i] != '\n')
	{
		length++;
		i++;
	}
	path_sorter(res, buf, start, length);
	return (1);
}

int			parse_sprite(t_res *res, char *buf)
{
	int		i;
	int		length;
	int		start;

	if (!buf)
		return (0);
	i = 0;
	length = 0;
	while (buf[i] != ' ')
		i++;
	while (buf[i] == ' ')
		i++;
	start = i;
	while (buf[i] && buf[i] != '\n')
	{
		length++;
		i++;
	}
	res->S = malloc(length + 1);
	ft_strlcpy(res->S, &buf[start], length + 1);
	return (1);
}

int			inv(t_vars *vars, int n)
{
	if (n != 3 && n != 5 && n != 7 && n != 21 && \
			n != 9 && n != 25 && n != 1 && n != 49)
    {
//        *ret = -1;
		exit_game(vars, 1, 5);
    }
	return (1);
}

int			is_end(t_vars *vars, int w, int h)
{
	int		ret;

	ret = 0;
	if (h == 0 || w == vars->collumn[h] - 1 || h == (vars->map_h - 1) || w == 0)
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
		while (w < vars->collumn[h])
		{
            is_end(vars, w, h);
			w++;
		}
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

int			parse_map(t_vars *vars, int fd)
{
	int			length;
	int			j;
	char		*buf;
	int			h;
	int			bol;

	bol = 0;
	h = 0;
	while (get_next_line(fd, &buf) != 0 || ft_strchr(buf, '1'))
	{
		if (buf[0] != '\n' && !empty_line(buf))
		{
			length = ft_strlen(buf);
			j = realloc_map(vars, length, h);
            vars->to_free->map = 1;
            vars->to_free->collumn = 1;
			bol = parse_map_string(vars, buf, h, &j);
			h++;
		}
		free(buf);
	}
	free(buf);
	if (bol != 1)
		exit_game(vars, 1, 2);
	return (h);
}
