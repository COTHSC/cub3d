/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 19:55:54 by jean              #+#    #+#             */
/*   Updated: 2021/04/01 11:09:24 by jescully         ###   ########.fr       */
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
	ft_strlcpy(vars->error[0], "Invalid args", 100);
	ft_strlcpy(vars->error[1], "Incomplete config file", 100);
	ft_strlcpy(vars->error[2], "Invalid or duplicate starting pos", 100);
	ft_strlcpy(vars->error[3], "Incorrect arg in config file", 100);
	ft_strlcpy(vars->error[4], "Invalid arg number", 100);
	ft_strlcpy(vars->error[5], "Invalid map", 100);
	ft_strlcpy(vars->error[6], "Invalid textures", 100);
	ft_strlcpy(vars->error[7], "Error/n", 100);
	ft_strlcpy(vars->error[8], "Invalid char in map", 100);
	ft_strlcpy(vars->error[9], "Error/n", 100);
}
