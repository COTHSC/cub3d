/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:23:04 by jescully          #+#    #+#             */
/*   Updated: 2021/03/17 14:42:00 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

int			parse_lines(t_vars *vars, int fd)
{
	char	**farray;
	char	*buf;
	int		c;
	int		h;
	int		j;
	fptr	functions[8];

	h = 0;
	vars->res->count = 0;
	farray = malloc(sizeof(char *) * 8);
	innit_arrayf(farray, functions, vars->res);
	while (get_next_line(fd, &buf) != 0)
	{
		c = 0;
		j = 0;
		while (ft_isspace(buf[j]))
			j++;
		while (c < 8)
		{
			if (!empty_line(buf))
				++vars->res->count;
			if (!ft_strncmp(&buf[j], farray[c], ft_strlen(farray[c])))
			{
				if (!(*functions[c])(vars->res, &buf[j]))
				{
					printf("Error\n funct\n");
                    free_farray(farray);
					exit_game(vars, 1);
				}

			}
			c++;
		}
		if (check_struct(vars->res))
		{
			h = parse_map(vars, fd);
			free(buf);
			free_farray(farray);
			return (h);
		}
		free(buf);
	}
	free_farray(farray);
	printf("Error\n Incomplete config\n");
	exit_game(vars, 0);
	return (0);
}

void         i_through_space(int *i, char *str)
{
    while (ft_isspace(str[*i]))
            *i++;
}

int			parse_colors(t_res *res, char *buf)
{
	int		r;
	int		g;
	int		b;
	int		i;
	int		color;

	i = 0;
	color = 0;
	if (!buf)
		return (0);
	while (!ft_isdigit(buf[i]))
	{
		if (!ft_isspace(buf[i]) && buf[i] != 'F' && buf[i] != 'C')
			return (0);
		i++;
	}
	r = ft_atoi(&buf[i]);
	while (buf[i] != ',')
	{
		if (!ft_isdigit(buf[i]) && !ft_isspace(buf[i]))
			return (0);
		i++;
	}
	g = ft_atoi(&buf[i + 1]);
	while (buf[++i] != ',')
	{
		if (!ft_isdigit(buf[i]) && !ft_isspace(buf[i]))
			return (0);
	}
	if (!ft_isdigit(buf[i + 1]))
		return 0;
	b = ft_atoi(&buf[++i]);
	while (ft_isdigit(buf[i]))
		i++;
	i -= 1;
	while (buf[++i] && buf[i] != '\n')
		if (!ft_isspace(buf[i]))
			return (0);
	if ( r > 255 || g > 255 || b > 255)
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

	if (!buf)
		return (0);
	i = 0;
	while (!ft_isdigit(buf[i]))
	{
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != 'R')
			return (0);
		i++;

	}
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
	if (ft_strnstr(buf, "NO", 3))
	{
		res->NO = malloc(length + 1);
		ft_strlcpy(res->NO, &buf[start], length + 1);
	}
	else if (ft_strnstr(buf, "SO", 3))
	{
		res->SO = malloc(length + 1);
		ft_strlcpy(res->SO, &buf[start], length + 1);
	}
	else if (ft_strnstr(buf, "WE", 3))
	{
		res->WE = malloc(length + 1);
		ft_strlcpy(res->WE, &buf[start], length + 1);
	}
	else if (ft_strnstr(buf, "EA", 3))
	{
		res->EA = malloc(length + 1);
		ft_strlcpy(res->EA, &buf[start], length + 1);
	}
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

int         inv(int *ret, int n)
{
    if (n != 3 && n != 5 && n != 7 && n != 21 && n != 9 && n != 25 && n != 1 && n!= 49)
    {
        *ret = -1;
        return (0);
    }
    return (1);
}

int is_end(t_vars *vars, int w, int h)
{
    if (h == 0 || w == vars->collumn[h] || h == (vars->map_h - 1))
        return (1);
    return (0);
}

int			check_map(t_vars *vars)
{
	int		h;
	int		w;
	int		ret;

	h = 1;
	ret = 0;
    w = 0;
	while (h < vars->map_h)
	{
		w = 1;
		while (w < vars->collumn[h] && (w < vars->collumn[h - 1] || h == 1))
		{
		    inv(&ret, get_value(vars, h, w) * get_value(vars, h - 1, w));
		    inv(&ret, get_value(vars, h, w) * get_value(vars, h, w - 1));
		    inv(&ret, get_value(vars, h, w) * get_value(vars, h - 1, w - 1));
		    w++;
		}
		h++;
	}
	h = 0;
	while (h < (vars->map_h - 1))
	{
		w = 0;
		while (w < vars->collumn[h] - 1 && (w < vars->collumn[h + 1]  || h == 0))
		{
		    inv(&ret, get_value(vars, h, w) * get_value(vars, h, w + 1));
		    inv(&ret, get_value(vars, h, w) * get_value(vars, h + 1, w));
		    inv(&ret, get_value(vars, h, w) * get_value(vars, h + 1, w + 1));
		    w++;
		}
		h++;
	}

	h = 1;
    while (h < (vars->map_h))
	{
		w = 0;
		while (w < vars->collumn[h] && (w < vars->collumn[h - 1] || h == 1))
		{
            if (get_value(vars, h, w) == 3 && w + 1 >= vars->collumn[h - 1])
                return (-1);
		    inv(&ret, get_value(vars, h, w) * get_value(vars, h - 1, w + 1));
		    w++;
		}
		h++;
	}
    h = 0;
    while (h < vars->map_h)
	{
		w = 0;
		while (w < vars->collumn[h])
		{
            if (is_end(vars, w, h) && get_value(vars, h, w) == 3)
                ret = -1;
            if (is_end(vars, w, h) && get_value(vars, h, w) == 7)
                ret = -1;
		    w++;
		}
		h++;
	}
	return (ret);
}

int			parse_map(t_vars *vars, int fd)
{
	int			length;
	int			j;
	int			i;
	char 		*buf;
	int 		h;
	int bol;
	
	bol = 0;
	h = 0;
	while(get_next_line(fd, &buf) != 0 || ft_strchr(buf, '1'))
	{
		if (buf[0] != '\n' && !empty_line(buf))
		{
			length = ft_strlen(buf);
			j = realloc_map(vars, length, h);
			i = -1;
			while (buf[++i])
			{
				if (buf[i] == '1')
					*(vars->map + sia(vars->collumn, h) + j++) = 1;
				else if (buf[i] == '0')
					*(vars->map + sia(vars->collumn, h) + j++) = 3;
				else if (buf[i] == '2')
					*(vars->map + sia(vars->collumn, h) + j++) = 7;
				else if (ft_strchr("NSEW", buf[i]))
				{
					*(vars->map + sia(vars->collumn, h) + j++) = 3;
					save_position(vars, buf[i], h, j);
					bol++;
				}
				else if (buf[i] == ' ')
					*(vars->map + sia(vars->collumn, h) + j++) = 5;
				else
				{
					printf("Error\n");
                    free(buf);
					exit_game(vars, 0);
				}

			}
			h++;
		}
		free(buf);

	}
	free(buf);
	if (bol != 1)
	{
		printf("Error\nPlayer pos not fount or duplicate");
		exit_game(vars, 0);
	}
	return (h);
}
