/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:49:28 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/10 12:21:36 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

static char	*copy_map(char *line)
{
	int		i;
	char	*map;

	i = 0;
	map = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!map)
		return (NULL);
	while (line[i])
	{
		map[i] = line[i];
		i++;
	}
	return (map);
}

static void fill_map(t_data *vars)
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

t_data	*take_map_2(int fd, t_data *vars)
{
	vars->path->path_north = ft_strdup(get_next_line(fd));
	vars->path->path_south = ft_strdup(get_next_line(fd));
	vars->path->path_west = ft_strdup(get_next_line(fd));
	vars->path->path_east = ft_strdup(get_next_line(fd));
	get_next_line(fd);
	vars->path->sol = ft_strdup(get_next_line(fd));
	vars->path->plafond = ft_strdup(get_next_line(fd));
	test_file(vars);
	get_next_line(fd);
	return (vars);
}


t_data	*take_map(int fd, t_data *vars)
{
	int		i;
	char	*line;

	i = 0;
	vars = take_map_2(fd, vars);
	line = get_next_line(fd);
	vars->size_line = ft_strlen(line);
	while (line)
	{
		vars->map[i] = copy_map(line);
		if (ft_strlen(vars->map[i]) > vars->size_line)
			vars->size_line = ft_strlen(vars->map[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (map_is_close(vars) == 1)
		fill_map(vars);
	else
		vars->error = 1;	
	return (vars);
}

/*t_data	*take_map(int fd, t_data *vars)
{
	char	*line;
	int		nb;

	nb = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "NO", 2) == 0)
			vars->path->path_north = ft_strdup(line + 3);
		else if (ft_strncmp(line, "SO", 2) == 0)
			vars->path->path_south = ft_strdup(line + 3);
		else if (ft_strncmp(line, "WE", 2) == 0)
			vars->path->path_west = ft_strdup(line + 3);
		else if (ft_strncmp(line, "EA", 2) == 0)
			vars->path->path_east = ft_strdup(line + 3);
		else if (ft_strncmp(line, "F ", 2) == 0)
			vars->path->sol = ft_strdup(line + 2);
		else if (ft_strncmp(line, "C ", 2))
			vars->path->plafond = ft_strdup(line + 2);
		if (ft_strncmp(line, "\n", 1) != 0)
			nb++;
		free(line);
		if (nb == 6)
			break;
		line = get_next_line(fd);
	}
	vars = take_map2(fd, vars);
	return (vars);
}*/

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

t_data *carac_is_valid(t_data *vars)
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

t_data *position_init(t_data *vars)
{
	int	i;
	int	j;
	int	spawn;

	spawn = 0;
	i = 0;
	while(vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'E'
				|| vars->map[i][j] == 'W' || vars->map[i][j] == 'S')
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
				if (ft_strchr(" \n" ,vars->map[i + 1][j])
					|| ft_strchr(" \n" ,vars->map[i - 1][j])
					|| ft_strchr(" \n" ,vars->map[i][j + 1])
					|| ft_strchr(" \n" ,vars->map[i][j - 1]))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

t_data *map_is_valid(t_data *vars)
{
//	flood_fill(vars);
	vars = carac_is_valid(vars);
	vars = position_init(vars);
	return(vars);
}
