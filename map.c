/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:49:28 by bhennequ          #+#    #+#             */
/*   Updated: 2023/07/21 20:48:03 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static char	*copy_map(char *line)
{
	int		i;
	char	*map;

	i = 0;
	map = malloc(sizeof(char) * (ft_strlen(line) + 1));
	while (line[i])
	{
		map[i] = line[i];
		i++;
	}
	return (map);
}

t_data *fill_map(t_data *vars)
{
	int	i;
	int	j;
	char	*line;

	i = 0;
	line = malloc(sizeof(char) * (vars->max_size + 1));
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == ' ')
				line[j] = '1';
			else if (vars->map[i][j] == '\n')
			{
				while (j < vars->max_size)
				{
					line[j] = '1';
					j++;
				}
				line[j] = '\n';
				break ;
			}
			else
				line[j] = vars->map[i][j];
			j++;
		}
		free(vars->map[i]);
		vars->map[i] = ft_strdup(line);
		i++;
	}
	free(line);
	return (vars);
}

t_data	*take_map(int fd, t_data *vars)
{
	int	i;
	char	*line;

	i = 0;
	vars->path_north = ft_strdup(get_next_line(fd));
	vars->path_south = ft_strdup(get_next_line(fd));
	vars->path_west = ft_strdup(get_next_line(fd));
	vars->path_east = ft_strdup(get_next_line(fd));
	line = get_next_line(fd);
	vars->sol = ft_strdup(get_next_line(fd));
	vars->plafond = ft_strdup(get_next_line(fd));
	line = get_next_line(fd);
	line = get_next_line(fd);
	vars->max_size = ft_strlen(line);
	while (line)
	{
		vars->map[i] = copy_map(line);
		if (ft_strlen(vars->map[i]) > vars->max_size)
			vars->max_size = ft_strlen(vars->map[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (vars);
}

/*static void	f_fill(t_data *vars, int x, int y, char target)
{
	if (x < 0 || y < 0 || x > ft_strlen(vars->map[x]) || vars->map[x][y + 1] == '\0')
		return ;
	if (vars->map[x][y] == 'F' || vars->map[x][y] != target)
		return ;
	vars->map[x][y] = 'F';
	f_fill(vars, x - 1, y, target);
	f_fill(vars, x + 1, y, target);
	f_fill(vars, x, y - 1, target);
	f_fill(vars, x, y + 1, target);	
}

static int	flood_fill(t_data *vars)
{
	int		i;
	int		j;
	t_point	start;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'E'
				|| vars->map[i][j] == 'W' || vars->map[i][j] == 'S')
			{
				start.x = i;
				start.y = j;
				break ;
			}
			j++;
		}
		i++;
	}
	f_fill(vars, start.x, start.y, '0');
	return (1);
}*/

int	carac_is_valid(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] != '0' && vars->map[i][j] != '1'
				&& vars->map[i][j] != 'N' && vars->map[i][j] != 'W'
				&& vars->map[i][j] != 'E' && vars->map[i][j] != 'S'
				&& vars->map[i][j] != '\n' && vars->map[i][j] != '\0'
				&& vars->map[i][j] != ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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
				if (ft_strchr(" \n\0",vars->map[i + 1][j]) != NULL
					|| ft_strchr(" \n\0",vars->map[i - 1][j]) != NULL
					|| ft_strchr(" \n\0",vars->map[i][j + 1]) != NULL
					|| ft_strchr(" \n\0",vars->map[i][j - 1]) != NULL)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	one_spawn(t_data *vars)
{
	int	i;
	int	j;
	int	spawn;

	i = 0;
	spawn = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'E'
				|| vars->map[i][j] == 'W' || vars->map[i][j] == 'S')
				spawn++;
			j++;
		}
		i++;
	}
	return (spawn);
}

int	map_is_valid(t_data *vars)
{
	if (one_spawn(vars) == 1 && carac_is_valid(vars) == 1 && map_is_close(vars) == 1)
	{
		vars = fill_map(vars);
		return (1);
	}
	return (0);
}
