/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:56:30 by jescully          #+#    #+#             */
/*   Updated: 2021/03/13 14:56:32 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	render_next_frame(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, \
			vars->img->ptr, vars->p->px, vars->p->py);
	mlx_destroy_image(vars->mlx, vars->img->ptr);
	return (1);
}
