/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sizemap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:51:05 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/24 14:20:39 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*take_size(t_data *vars, int fd, char *line)
{
	int	size;

	size = 0;
	while (ft_strncmp(line, "\n", 1) == 0)
		line = get_next_line(fd);
	while (line && ft_strncmp(line, "\n", 1) != 0)
	{
		free(line);
		line = get_next_line(fd);
		size++;
	}
	free(line);
	vars->size_map = size;
	return (vars);
}

t_data  *take_map_size(int fd, t_data *vars)
{
	char	*line;
	int		nb;

	nb = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line && nb < 6)
	{
		if (ft_strncmp(line, "\n", 1) != 0)
			nb++;
		free(line);
		line = get_next_line(fd);
	}
	vars = take_size(vars, fd, line);
	return (vars);
}
