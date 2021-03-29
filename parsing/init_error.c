/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:55:54 by jean              #+#    #+#             */
/*   Updated: 2021/03/28 20:56:05 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	init_error(t_vars *vars)
{
	int i;

	i = 0;
	if (!(vars->error = malloc(sizeof(char *) * 10)))
		return ;
	while (i < 10)
		vars->error[i++] = malloc(100);
	ft_strlcpy(vars->error[0], "invalid args", 100);
	ft_strlcpy(vars->error[1], "incomplete config", 100);
	ft_strlcpy(vars->error[2], "invalid or duplicate starting pos", 100);
	ft_strlcpy(vars->error[3], "incorrect arg in config file", 100);
	ft_strlcpy(vars->error[4], "invalid arg number", 100);
	ft_strlcpy(vars->error[5], "invalid map", 100);
	ft_strlcpy(vars->error[6], "invalid textures", 100);
	ft_strlcpy(vars->error[7], "Error/n", 100);
	ft_strlcpy(vars->error[8], "invalid char in map", 100);
	ft_strlcpy(vars->error[9], "Error/n", 100);
}
