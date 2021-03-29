/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 20:54:30 by jean              #+#    #+#             */
/*   Updated: 2021/03/28 20:55:17 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	check_max_screen_size(t_vars *vars)
{
	int	maxx;
	int	maxy;

	maxx = 5000;
	maxy = 5000;
	if (!vars->save)
		mlx_get_screen_size(vars->mlx, &maxx, &maxy);
	if (maxx < vars->res->w)
		vars->res->w = maxx;
	if (maxy < vars->res->h)
		vars->res->h = maxy;
}
