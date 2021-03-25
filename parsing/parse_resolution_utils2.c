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
			
}

int			check_forbidden_char(char *buf, char *permitted)
{
	int i;
	int j;
	int yes;

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
			return 0;
	}
	return (1);
}

int			ft_get_color(int r, int g, int b)
{
	int		color;

	color = 0;
	color += r << 16;
	color += g << 8;
	color += b;
	return (color);
}

void		*ft_realloc(void *ptr, int size, int newsize)
{
	char	*str;
	char	*new;
	int		i;

	str = (char*)ptr;
	if (!(new = (char*)malloc(sizeof(char) * newsize + 1)))
	{
		if (ptr && size != 0)
			free(ptr);
		return (NULL);
	}
	i = -1;
	while (++i < size)
		*(new + i) = *(str + i);
	while (i < newsize)
		*(new + i++) = '\0';
	if (ptr && size != 0)
		free(ptr);
	return (new);
}

int			array_length(int *array)
{
	int		length;

	length = 0;
	while (array[length])
		length++;
	return (length);
}

int			sia(int *array, int h)
{
	int		result;
	int		count;

	result = 0;
	count = 0;
	while (count < h)
	{
		result = result + array[count];
		count++;
	}
	return (result);
}

int				realloc_map(t_vars *vars, int length, int h)
{
	static int	arlength;
	static int	nc;

	if (h == 0)
	{
		nc = 0;
		arlength = (length + 1) * sizeof(int);
		vars->collumn = (int *)malloc(sizeof(int));
		vars->collumn[nc] = length;
		vars->map = (int *)malloc(sizeof(int) * length * (h + 2));
	}
	else
	{
		vars->collumn = (int *)ft_realloc(vars->collumn, sizeof(int) \
				* (nc + 1), sizeof(int) * (nc + 2));
		vars->collumn[++nc] = length;
		vars->map = (int *)ft_realloc(vars->map, arlength, sizeof(int) \
				* length + arlength);
		arlength += (length) * sizeof(int);
	}
	return (0);
}
