/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution_utils1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:23:04 by jescully          #+#    #+#             */
/*   Updated: 2021/03/29 19:32:33 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <fcntl.h>

int			innit_arrayf(fptr functions[8], t_vars *vars)
{
	int		i;

	i = 0;
	while (i < 8)
		vars->farray[i++] = malloc(sizeof(char) * 4);
	ft_strlcpy(vars->farray[0], "R ", 4);
	ft_strlcpy(vars->farray[1], "NO ", 4);
	ft_strlcpy(vars->farray[2], "SO ", 4);
	ft_strlcpy(vars->farray[3], "WE ", 4);
	ft_strlcpy(vars->farray[4], "EA ", 4);
	ft_strlcpy(vars->farray[5], "S ", 4);
	ft_strlcpy(vars->farray[6], "F ", 4);
	ft_strlcpy(vars->farray[7], "C ", 4);
	functions[0] = &parse_resolution;
	functions[1] = &parse_paths;
	functions[2] = &parse_paths;
	functions[3] = &parse_paths;
	functions[4] = &parse_paths;
	functions[5] = &parse_sprite;
	functions[6] = &parse_colors;
	functions[7] = &parse_colors;
	vars->res->F = -1;
	vars->res->C = -1;
	return (1);
}

void		free_farray(char **farray)
{
	int		c;

	c = 0;
	while (c < 8)
		free(farray[c++]);
	free(farray);
}

int			ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int			empty_line(char *str)
{
	while (*str++)
		if (!ft_isspace(*str))
			return (0);
	return (1);
}

int			check_forbidden_char(char *buf, char *permitted)
{
	int		i;
	int		j;
	int		yes;

	yes = 0;
	j = 0;
	while (buf[j])
	{
		i = 0;
		while (permitted[i])
		{
			if (buf[i] == permitted[i])
				yes++;
		}
		if (yes != 1)
			return (0);
	}
	return (1);
}
