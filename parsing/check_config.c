/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:22:32 by jescully          #+#    #+#             */
/*   Updated: 2021/04/02 11:34:14 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_paths(t_res *res)
{
	int fd;

	if ((fd = open(res->no, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	if ((fd = open(res->so, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	if ((fd = open(res->we, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	if ((fd = open(res->ea, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	return (1);
}

int	check_struct(t_res *res)
{
	if (res->w <= 0)
		return (0);
	if (res->h <= 0)
		return (0);
	if (res->f < 0)
		return (0);
	if (res->c < 0)
		return (0);
	if (res->no == NULL)
		return (0);
	if (res->so == NULL)
		return (0);
	if (res->we == NULL)
		return (0);
	if (res->ea == NULL)
		return (0);
	if (res->s == NULL)
		return (0);
	if (!check_paths(res))
		return (0);
	if ((res->count / 8) != 8)
		return (0);
	return (1);
}
