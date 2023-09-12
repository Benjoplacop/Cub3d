/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:11:46 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 15:21:29 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*skip_no_line(int fd)
{
	char	*line;

	line = get_next_line(fd, 0);
	while (ft_strncmp(line, "\n", 1) == 0)
	{
		free(line);
		line = get_next_line(fd, 0);
	}
	return (line);
}

t_data	*take_map2(int fd, t_data *vars)
{
	int		i;
	char	*line;

	i = 0;
	line = skip_no_line(fd);
	vars->size_line = ft_strlen(line);
	while (line)
	{
		vars->map[i] = ft_strdup(line);
		if (ft_strlen(vars->map[i]) > vars->size_line && line)
			vars->size_line = ft_strlen(vars->map[i]);
		free(line);
		line = get_next_line(fd, 0);
		i++;
	}
	vars->map[i] = NULL;
	free(line);
	if (map_is_close(vars) == 1)
		fill_map(vars);
	else
		vars->error = 1;
	return (vars);
}

int	take_path_on_parsing(t_data *vars, char *line, int nb)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		vars->path->path_north = ft_strdup(line + 3);
	if (ft_strncmp(line, "SO", 2) == 0)
		vars->path->path_south = ft_strdup(line + 3);
	if (ft_strncmp(line, "WE", 2) == 0)
		vars->path->path_west = ft_strdup(line + 3);
	if (ft_strncmp(line, "EA", 2) == 0)
		vars->path->path_east = ft_strdup(line + 3);
	if (ft_strncmp(line, "F ", 2) == 0)
		vars->path->sol = ft_strdup(line + 2);
	if (ft_strncmp(line, "C ", 2) == 0)
		vars->path->plafond = ft_strdup(line + 2);
	if (ft_strncmp(line, "\n", 2) != 0)
		nb++;
	return (nb);
}

t_data	*take_map(int fd, t_data *vars)
{
	char	*line;
	int		nb;

	nb = 0;
	line = get_next_line(fd, 0);
	while (line)
	{
		nb = take_path_on_parsing(vars, line, nb);
		free(line);
		if (nb == 6)
			break ;
		line = get_next_line(fd, 0);
	}
	vars = take_map2(fd, vars);
	return (vars);
}
