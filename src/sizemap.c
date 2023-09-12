/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:51:05 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 15:14:37 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*take_size(t_data *vars, int fd)
{
	int		size;
	char	*line;

	size = 0;
	line = get_next_line(fd, 0);
	while (ft_strncmp(line, "\n", 1) == 0)
	{
		free(line);
		line = get_next_line(fd, 0);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd, 0);
		size++;
	}
	free(line);
	vars->size_map = size;
	return (vars);
}

t_data	*take_map_size(int fd, t_data *vars)
{
	char	*line;
	int		nb;

	nb = 0;
	line = get_next_line(fd, 0);
	if (ft_strncmp(line, "\n", 1) != 0)
		nb++;
	while (line && nb < 6)
	{
		free(line);
		line = get_next_line(fd, 0);
		if (ft_strncmp(line, "\n", 1) != 0)
			nb++;
	}
	free(line);
	vars = take_size(vars, fd);
	vars->map = malloc(sizeof(char *) * (vars->size_map + 1));
	if (!vars->map)
		return (NULL);
	return (vars);
}
