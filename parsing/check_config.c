/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:22:32 by jescully          #+#    #+#             */
/*   Updated: 2021/03/17 10:14:26 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_paths(t_res *res)
{
	int fd;

	if ((fd = open(res->NO, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	if ((fd = open(res->SO, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	if ((fd = open(res->WE, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	if ((fd = open(res->EA, O_RDONLY)) == -1)
		return (0);
	else
		close(fd);
	return 1;
}

int	check_struct(t_res *res)
{
	if (res->w <= 0)
		return (0);
	if (res->h <= 0)
		return (0);
	if (res->F < 0)
		return (0);
	if (res->C < 0)
		return (0);
	if (res->NO == NULL)
		return (0);
	if (res->SO == NULL)
		return (0);
	if (res->WE == NULL)
		return (0);
	if (res->EA == NULL)
		return (0);
	if (res->S == NULL)
		return (0);
	if (!check_paths(res))
		return (0);
	if ((res->count / 8) != 8)
		return (0);
	return (1);
}
