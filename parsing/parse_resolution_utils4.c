/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution_utils4.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 21:12:59 by jean              #+#    #+#             */
/*   Updated: 2021/04/02 10:13:38 by jescully         ###   ########.fr       */
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

int			parse_colors(t_res *res, char *buf)
{
	int		r;
	int		g;
	int		b;
	int		i;
	int		color;

	i = -1;
	color = 0;
	if (!ft_advance(buf, &r, &g, &b))
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
	i -= 1;
	while (!ft_isdigit(buf[++i]) && buf[i])
		if (buf[i] != ' ' && buf[i] != '\t' && buf[i] != 'R')
			return (0);
	res->h = ft_atoi(&buf[i]);
	while (ft_isdigit(buf[i]))
		i++;
	i -= 1;
	while (buf[++i] && buf[i] != '\n')
		if (!ft_isspace(buf[i]))
		{
			free(buf);
			return (0);
		}
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
