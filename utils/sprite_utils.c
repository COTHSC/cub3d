/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:57:10 by jescully          #+#    #+#             */
/*   Updated: 2021/04/01 13:34:55 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			swap_sprites(t_sprites *sprite1, t_sprites *sprite2)
{
	t_sprites	*dummy;

	dummy = malloc(sizeof(t_sprites));
	dummy->dist = 0;
	dummy->x = 0.0;
	dummy->y = 0.0;
	dummy->dist = sprite2->dist;
	dummy->x = sprite2->x;
	dummy->y = sprite2->y;
	sprite2->dist = sprite1->dist;
	sprite2->x = sprite1->x;
	sprite2->y = sprite1->y;
	sprite1->dist = dummy->dist;
	sprite1->x = dummy->x;
	sprite1->y = dummy->y;
	free(dummy);
}

int				sprite_sort(t_sprites **sprite, int num_sprites)
{
	int			i;
	int			done;

	i = 0;
	done = 0;
	while (i < num_sprites - 1)
	{
		if (sprite[i]->dist < sprite[i + 1]->dist)
		{
			swap_sprites(sprite[i], sprite[i + 1]);
			done++;
		}
		i++;
	}
	if (done != 0)
		sprite_sort(sprite, num_sprites);
	else
		return (1);
	return (1);
}

int				count_sprites(t_vars *vars)
{
	int			h;
	int			w;
	int			num_sprite;

	h = 0;
	num_sprite = 0;
	while (h < vars->map_h)
	{
		w = 0;
		while (w < vars->collumn[h])
		{
			if (get_value(vars, h, w) == 7)
				num_sprite++;
			w++;
		}
		h++;
	}
	return (num_sprite);
}

int				init_sprites(t_vars *vars)
{
	int			i;
	int			num_sprite;

	vars->to_free->sprites = 1;
	i = 0;
	num_sprite = count_sprites(vars);
	vars->sprites = malloc(sizeof(t_sprites*) * (num_sprite));
	i = 0;
	while (i < num_sprite)
		vars->sprites[i++] = malloc(sizeof(t_sprites));
	spritefinder(vars->sprites, vars);
	return (1);
}

int				free_sprites(t_vars *vars)
{
	int			num_sprites;
	int			i;

	num_sprites = count_sprites(vars);
	i = 0;
	while (i < num_sprites)
		if (vars->sprite[i].ptr)
			free(vars->sprites[i++]);
	if (vars->sprite)
		free(vars->sprites);
	return (1);
}
