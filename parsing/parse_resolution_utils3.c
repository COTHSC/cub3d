/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution_utils3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 21:12:59 by jean              #+#    #+#             */
/*   Updated: 2021/04/02 11:36:12 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

void			path_sorter(t_res *res, char *buf, int start, int length)
{
	if (ft_strnstr(buf, "NO", 3) && !res->no)
	{
		res->no = malloc(length + 1);
		ft_strlcpy(res->no, &buf[start], length + 1);
	}
	else if (ft_strnstr(buf, "SO", 3) && !res->so)
	{
		res->so = malloc(length + 1);
		ft_strlcpy(res->so, &buf[start], length + 1);
	}
	else if (ft_strnstr(buf, "WE", 3) && !res->we)
	{
		res->we = malloc(length + 1);
		ft_strlcpy(res->we, &buf[start], length + 1);
	}
	else if (ft_strnstr(buf, "EA", 3) && !res->ea)
	{
		res->ea = malloc(length + 1);
		ft_strlcpy(res->ea, &buf[start], length + 1);
	}
}

static void		get_out(t_vars *vars, char *buf)
{
	free(buf);
	exit_game(vars, 1, 8);
}

int				parse_map_string(t_vars *vars, char *buf, int h, int *c)
{
	int			i;
	static int	bol = 0;

	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '1')
			*(vars->map + sia(vars->collumn, h) + *c) = 1;
		else if (buf[i] == '0')
			*(vars->map + sia(vars->collumn, h) + *c) = 3;
		else if (buf[i] == '2')
			*(vars->map + sia(vars->collumn, h) + *c) = 7;
		else if (ft_strchr("NSEW", buf[i]))
		{
			*(vars->map + sia(vars->collumn, h) + *c) = 3;
			bol += save_position(vars, buf[i], h, *c + 1);
		}
		else if (buf[i] == ' ')
			*(vars->map + sia(vars->collumn, h) + *c) = 5;
		else
			get_out(vars, buf);
		*c += 1;
	}
	return (bol);
}

int				ft_advance(char *buf, int *r, int *g, int *b)
{
	int			i;

	i = -1;
	while (!ft_isdigit(buf[++i]))
		if (!ft_isspace(buf[i]) && buf[i] != 'F' && buf[i] != 'C')
			return (0);
	*r = ft_atoi(&buf[i]);
	while (buf[i] != ',')
	{
		if (!ft_isdigit(buf[i]) && !ft_isspace(buf[i]))
			return (0);
		i++;
	}
	*g = ft_atoi(&buf[i + 1]);
	while (buf[++i] != ',')
		if (!ft_isdigit(buf[i]) && !ft_isspace(buf[i]))
			return (0);
	if (!ft_isdigit(buf[i + 1]))
		return (0);
	*b = ft_atoi(&buf[++i]);
	while (ft_isdigit(buf[i]))
		i++;
	if (!empty_line(&buf[i]))
		return (0);
	return (1);
}
