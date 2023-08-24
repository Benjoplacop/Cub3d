/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:49:28 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/24 14:08:24 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	fill_map(t_data *vars)
{
	int		i;
	int		j;
	char	*line;

	line = malloc(sizeof(char) * (vars->size_line + 1));
	if (!line)
		return ;
	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '\n')
			{
				while (j < vars->size_line)
				{
					line[j] = '1';
					j++;
				}
				line[j] = '\n';
				break ;
			}
			line[j] = vars->map[i][j];
			j++;
		}
		line[j] = '\0';
		free(vars->map[i]);
		vars->map[i] = ft_strdup(line);
		i++;
	}
	free(line);
}

void	test_file(t_data *vars)
{
	if (vars->path->path_north == NULL || vars->path->path_south == NULL
		|| vars->path->path_east == NULL || vars->path->path_west == NULL
		|| vars->path->sol == NULL || vars->path->plafond == NULL)
		vars->error = 1;
}

t_data	*take_map2(int fd, t_data *vars)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	line = get_next_line(fd);
	while (ft_strncmp(line, "\n", 1) == 0)
		line = get_next_line(fd);
	vars->size_line = ft_strlen(line);
	while (line)
	{
		vars->map[i] = ft_strdup(line);
		if (ft_strlen(vars->map[i]) > vars->size_line && line)
			vars->size_line = ft_strlen(vars->map[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	vars->map[i] = NULL;
	if (map_is_close(vars) == 1)
		fill_map(vars);
	else
		vars->error = 1;
	return (vars);
}

t_data	*take_map(int fd, t_data *vars)
{
	char	*line;
	int		nb;

	nb = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line)
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
		if (ft_strncmp(line, "\n", 1) != 0)
			nb++;
		free(line);
		if (nb == 6)
			break ;
		line = get_next_line(fd);
	}
	vars->map = malloc(sizeof(char *) * (vars->size_map + 1));
	if (!vars->map)
		return (NULL);
	vars = take_map2(fd, vars);
	return (vars);
}

t_data	*carac_is_valid(t_data *vars)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			c = vars->map[i][j];
			if (c != '0' && c != '1' && c != 'N'
				&& c != 'W' && c != 'E' && c != 'S'
				&& c != '\n' && c != '\0'
				&& c != ' ')
			{
				vars->error = 1;
				return (vars);
			}
			j++;
		}
		i++;
	}
	return (vars);
}

t_data	*position_init(t_data *vars)
{
	int		i;
	int		j;
	int		spawn;
	char	c;

	spawn = 0;
	i = 0;
	vars->init_pos.x = 0;
	vars->init_pos.y = 0;
	vars->init_pos.dir = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			c = vars->map[i][j];
			if (c == 'N' || c == 'E'
				|| c == 'W' || c == 'S')
			{
				spawn++;
				vars->init_pos.x = i;
				vars->init_pos.y = j;
				vars->init_pos.dir = vars->map[i][j];
				vars->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (spawn == 1)
		return (vars);
	vars->error = 1;
	return (vars);
}

int	map_is_close(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '0')
			{
				if (ft_strchr(" \n\0", vars->map[i + 1][j])
					|| ft_strchr(" \n\0", vars->map[i - 1][j])
					|| ft_strchr(" \n\0", vars->map[i][j + 1])
					|| ft_strchr(" \n\0", vars->map[i][j - 1]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

t_data	*map_is_valid(t_data *vars)
{
	vars = carac_is_valid(vars);
	vars = position_init(vars);
	return (vars);
}
