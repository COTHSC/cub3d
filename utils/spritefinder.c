/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritefinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:56:58 by jescully          #+#    #+#             */
/*   Updated: 2021/03/13 14:57:04 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		innit_sprites(t_sprites **sprite, double x, double y, int num)
{
	sprite[num]->x = x;
	sprite[num]->y = y;
	sprite[num]->texture = 1;
	sprite[num]->dist = 1;
	return (1);
}

int		spritefinder(t_sprites **sprite, t_vars *vars)
{
	int w;
	int h;
	int i;

	w = 0;
	h = 0;
	i = 0;
	while (h < vars->map_h)
	{
		w = 0;
		while (w < vars->collumn[h])
		{
			if (get_value(vars, h, w) == 7)
			{
				innit_sprites(sprite, h + 0.5, w + 0.5, i);
				i++;
			}
			w++;
		}
		h++;
	}
	return (1);
}
