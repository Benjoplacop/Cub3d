/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:49:28 by bhennequ          #+#    #+#             */
/*   Updated: 2023/06/28 14:30:01 by bhennequ         ###   ########.fr       */
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
		if (line[i] == ' ')
			map[i] = '1';
		else
			map[i] = line[i];
		i++;
	}
	return (map);
}

static char	**fill_map(int size, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '\n')
			{
				while (j < size)
				{
					map[i][j] = '1';
					j++;
				}
				map[i][size] = '\n';
				break ;
			}
			j++;
		}
		i++;
	}
	return (map);
}

t_data	*take_map(int fd, t_data *vars)
{
	int		i;
	char	*line;
	int		size_line;

	i = 0;
	vars->path_north = ft_strdup(get_next_line(fd));
	vars->path_south = ft_strdup(get_next_line(fd));
	vars->path_west = ft_strdup(get_next_line(fd));
	vars->path_east = ft_strdup(get_next_line(fd));
	line = get_next_line(fd);
	vars->sol = ft_strdup(get_next_line(fd));
	vars->plafond = ft_strdup(get_next_line(fd));
	line = get_next_line(fd);
	size_line = ft_strlen(line);
	while (line)
	{
		vars->map[i] = copy_map(line);
		if (ft_strlen(vars->map[i]) > size_line)
			size_line = ft_strlen(vars->map[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	vars->map = fill_map(size_line, vars->map);	
	return (vars);
}

static void	f_fill(t_data *vars, int x, int y, char target)
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
}

/*int	check_map_contour(t_data *vars)
{

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
			if (vars->map[i][j] != '0' || vars->map[i][j] != '1'
				|| vars->map[i][j] != 'N' || vars->map[i][j] != 'W'
				|| vars->map[i][j] != 'E' || vars->map[i][j] != 'S'
				|| vars->map[i][j] != '\n' || vars->map[i][j] != '\0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	map_is_valid(t_data *vars)
{
	int	i;
	int	j;
	int	spawn;

	i = 0;
	spawn = 0;
	while (vars->map[i])
	{
		j = 0;
		if (vars->map[i][j] == '\n')
			spawn = 10;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'E'
				|| vars->map[i][j] == 'W' || vars->map[i][j] == 'S')
				spawn++;
			j++;
		}
		i++;
	}
	flood_fill(vars);
//	if (check_map_contour(vars) == 0)
//		return (0);
	vars->map = fill_map(size_line, vars->map);
	if (spawn == 1)
		return (1);
	return (0);
}
