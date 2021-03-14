/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 16:22:32 by jescully          #+#    #+#             */
/*   Updated: 2021/03/14 16:26:42 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_struct(t_res *res)
{
	if (res->w == 0)
		return (0);
	if (res->h == 0)
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
	return (1);
}
