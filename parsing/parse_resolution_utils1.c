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
/*
int			innit_arrayf(char **farray, fptr functions[8], t_res *res)
{
	int		i;

	i = 0;
	while (i < 8)
		farray[i++] = malloc(sizeof(char) * 4);
	ft_strlcpy(farray[0], "R ", 4);
	ft_strlcpy(farray[1], "NO ", 4);
	ft_strlcpy(farray[2], "SO ", 4);
	ft_strlcpy(farray[3], "WE ", 4);
	ft_strlcpy(farray[4], "EA ", 4);
	ft_strlcpy(farray[5], "S ", 4);
	ft_strlcpy(farray[6], "F ", 4);
	ft_strlcpy(farray[7], "C ", 4);
	functions[0] = &parse_resolution;
	functions[1] = &parse_paths;
	functions[2] = &parse_paths;
	functions[3] = &parse_paths;
	functions[4] = &parse_paths;
	functions[5] = &parse_sprite;
	functions[6] = &parse_colors;
	functions[7] = &parse_colors;
	res->F = -1;
	res->C = -1;
	return (1);
}

void	free_farray(char **farray)
{
	int c;

	c = 0;
	while (c < 8)
		free(farray[c++]);
	free(farray);
}
/*
int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}
int	empty_line(char *str)
{
	while  (*str++)
		if (!ft_isspace(*str))
			return (0);
	return (1);
			
}*/
