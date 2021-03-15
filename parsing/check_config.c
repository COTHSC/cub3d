/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:22:32 by jescully          #+#    #+#             */
/*   Updated: 2021/03/15 15:02:21 by jescully         ###   ########.fr       */
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
	{
		printf("paths 1\n");
		return (0);
	}
	if (res->h <= 0)
	{
		printf("paths2\n");
		return (0);
	}
	if (res->F < 0)
	{
		printf("paths3\n");
		return (0);
	}
	if (res->C < 0)
	{
		printf("paths4\n");
		return (0);
	}
	if (res->NO == NULL)
	{
		printf("paths5\n");
		return (0);
	}
	if (res->SO == NULL)
	{
		printf("paths6\n");
		return (0);
	}
	if (res->WE == NULL)
	{
		printf("paths7\n");
		return (0);
	}
	if (res->EA == NULL)
	{
		printf("paths8\n");
		return (0);
	}
	if (res->S == NULL)
	{
		printf("paths9\n");
		return (0);
	}
	if (!check_paths(res))
	{
		printf("paths10\n");
		return (0);
	}


	return (1);
}
