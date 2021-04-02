/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jescully <jescully@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 11:18:41 by jescully          #+#    #+#             */
/*   Updated: 2021/04/02 11:24:03 by jescully         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

int			load_image(t_vars *v, t_img *i, char *path)
{
	i->ptr = mlx_xpm_file_to_image(v->mlx, path, &i->width, &i->height);
	if (i->ptr == NULL)
		return (0);
	i->data = (int *)mlx_get_data_addr(i->ptr, &i->bpp, &i->size_l, &i->endian);
	return (1);
}

int			load_texture(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < 4)
		vars->text[i++] = (t_img *)malloc(sizeof(t_img));
	i = 0;
	i += load_image(vars, vars->text[0], vars->res->SO);
	i += load_image(vars, vars->text[1], vars->res->NO);
	i += load_image(vars, vars->text[2], vars->res->EA);
	i += load_image(vars, vars->text[3], vars->res->WE);
	vars->sprite = (t_img *)malloc(sizeof(t_img));
	i += load_image(vars, vars->sprite, vars->res->S);
	if (i == 5)
	{
		init_sprites(vars);
		if (vars->save == 1)
			draw_frame(vars);
		return (1);
	}
	exit_game(vars, 2, 6);
	return (0);
}
int		exit_the_cross(int keycode, t_vars *vars)
{
	int i;

	i = keycode;
	exit_game(vars, 0, 7);
	return (1);
}

void		init_to_zero(t_vars *vars)
{
	vars->to_free->farray = 0;
	vars->to_free->sprites = 0;
	vars->res->NO = 0;
	vars->res->EA = 0;
	vars->res->SO = 0;
	vars->res->WE = 0;
	vars->res->S = 0;
	vars->res->w = -1;
	vars->res->h = -1;
}

void		init_free_to_zero(t_vars *vars)
{
	vars->to_free->map = 0;
	vars->to_free->farray = 0;
	vars->to_free->sprites = 0;
}
