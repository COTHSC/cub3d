/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:25:35 by jean              #+#    #+#             */
/*   Updated: 2021/03/29 18:25:39 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../cub3d.h"
#include <fcntl.h>

void				write_header(t_vars *vars, int size, int fd)
{
	unsigned char	header[54];
	int				i;

	i = 0;
	while (i < 54)
		header[i++] = 0;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(vars->res->w);
	header[19] = (unsigned char)(vars->res->w >> 8);
	header[20] = (unsigned char)(vars->res->w >> 16);
	header[21] = (unsigned char)(vars->res->w >> 24);
	header[22] = (unsigned char)(vars->res->h);
	header[23] = (unsigned char)(vars->res->h >> 8);
	header[24] = (unsigned char)(vars->res->h >> 16);
	header[25] = (unsigned char)(vars->res->h >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
}

int					save_img(t_vars *vars)
{
	int				i;
	int				j;
	int				fd;

	j = vars->res->h;
	fd = open("./screenshot.bmp", O_CREAT | O_RDWR, S_IRWXU | S_IRWXG);
	write_header(vars, 54 + vars->res->h * vars->res->w, fd);
	while (j > 0)
	{
		i = 0;
		while (i < vars->res->w)
		{
			write(fd, &vars->img->data[j * (vars->img->size_l / 4) + i], 4);
			i++;
		}
		j--;
	}
	close(fd);
	return (0);
}
