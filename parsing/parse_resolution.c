/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:23:04 by jescully          #+#    #+#             */
/*   Updated: 2021/04/03 12:32:09 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

void		direct_function(t_vars *vars, t_fptr functions[8], char *buf)
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
			{
				free(buf);
				exit_game(vars, 1, 3);
			}
		}
		c++;
	}
	free(buf);
}

int			parse_lines(t_vars *vars, int fd)
{
	char	*buf;
	int		h;
	t_fptr	functions[8];

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
			return (h);
		}
	}
	exit_game(vars, 1, 1);
	return (0);
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
	if (!res->s)
	{
		res->s = malloc(length + 1);
		ft_strlcpy(res->s, &buf[start], length + 1);
	}
	return (1);
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
	while ((get_next_line(fd, &buf)) != 0 || ft_strchr(buf, '1'))
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
