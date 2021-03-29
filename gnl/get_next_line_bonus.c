/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jean <jescully@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 16:36:29 by jean              #+#    #+#             */
/*   Updated: 2020/12/08 21:26:00 by jean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*cleaned_up_line(char *line)
{
	int			i;
	char		*clean_line;

	i = 0;
	if (!line || ft_strlen(line) == 0)
	{
		clean_line = (char*)malloc(1);
		clean_line[0] = '\0';
		return (clean_line);
	}
	while (line[i] && line[i] != '\n')
		i++;
	if (!(clean_line = (char*)(malloc(sizeof(char) * (i + 1)))))
		return (NULL);
	ft_strlcpy(clean_line, line, i + 1);
	return (clean_line);
}

static char	*leftovers(char *available_string)
{
	static char *new_string;

	if (!available_string || ft_strlen(available_string) == 0)
		return (NULL);
	if (!ft_strchr(available_string, '\n'))
	{
		free(available_string);
		return (NULL);
	}
	new_string = ft_strdup(ft_strchr(available_string, '\n') + 1);
	free(available_string);
	return (new_string);
}

static int	check_the_input(char *bufstr, int const fd, char **line)
{
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 1024 || !bufstr || !line)
	{
		free(bufstr);
		line = NULL;
		return (0);
	}
	else
		return (1);
}

int			get_next_line(int const fd, char **line)
{
	static char *available_string[1024];
	char		*bufstr;
	int			bytes;

	if (!(bufstr = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	bytes = 1;
	if (!check_the_input(bufstr, fd, line))
		return (-1);
	while (!ft_strchr(available_string[fd], '\n') && bytes != 0)
	{
		if ((bytes = read(fd, bufstr, BUFFER_SIZE)) == -1)
		{
			free(bufstr);
			return (-1);
		}
		bufstr[bytes] = '\0';
		available_string[fd] = ft_strjoin(available_string[fd], bufstr);
	}
	free(bufstr);
	*line = cleaned_up_line(available_string[fd]);
	available_string[fd] = leftovers(available_string[fd]);
	bytes = ((bytes == 0 && ft_strlen(available_string[fd]) == 0) ? 0 : 1);
	return (bytes);
}
