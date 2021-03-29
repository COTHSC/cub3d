/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:54:54 by jescully          #+#    #+#             */
/*   Updated: 2021/03/28 20:03:24 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw(t_vars *vars)
{
	if (vars->save == 1)
	{
		save_img(vars);
		exit_game(vars, 3, 7);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->ptr, 0, 0);
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	free(vars->img);
}
