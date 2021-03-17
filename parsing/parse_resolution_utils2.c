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
