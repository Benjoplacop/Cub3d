/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:11:46 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/24 15:09:13 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*skip_no_line(int fd, t_data *vars)
{
	char	*line;

	line = get_next_line(fd, 0);
	while (ft_strncmp(line, "\n", 1) == 0 || ft_strncmp(line , "1", 1) != 0)
	{
		free(line);
		line = get_next_line(fd, 0);
		if (ft_strncmp(line, "\n", 1) != 0 && ft_strncmp(line, "1", 1) != 0)
		{
			free(line);
			vars->error = 1;
			return (NULL);
		}
	}
	return (line);
}

t_data	*take_map2(int fd, t_data *vars)
{
	int		i;
	char	*line;

	i = 0;
	line = skip_no_line(fd, vars);
	if (line == NULL)
		return (vars);
	vars->size_line = ft_strlen(line);
	while (line && (ft_strncmp(line, "1", 1) == 0
			|| ft_strncmp(line, " ", 1) == 0))
	{
		vars->map[i] = ft_strdup(line);
		if (ft_strlen(vars->map[i]) > vars->size_line && line)
			vars->size_line = ft_strlen(vars->map[i]);
		free(line);
		line = get_next_line(fd, 0);
		i++;
	}
	if (line)
	{
		free(line);
		line = get_next_line(fd, 1);
	}
	vars->map[i] = NULL;
	free(line);
	vars = take_map3(vars);
	return (vars);
}

t_data	*take_path_on_parsing_two(t_data *vars, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		vars->path->pn++;
		vars->path->path_north = dup_space(line + 3);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		vars->path->ps++;
		vars->path->path_south = dup_space(line + 3);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		vars->path->pw++;
		vars->path->path_west = dup_space(line + 3);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		vars->path->pe++;
		vars->path->path_east = dup_space(line + 3);
	}
	return (vars);
}

int	take_path_on_parsing(t_data *vars, char *line, int nb)
{
	vars = take_path_on_parsing_two(vars, line);
	if (ft_strncmp(line, "Door ", 5) == 0)
		vars->path->door = dup_space(line + 5);
	if (ft_strncmp(line, "F", 1) == 0)
	{
		vars->path->so++;
		vars->path->sol = dup_space(line + 2);
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		vars->path->pl++;
		vars->path->plafond = dup_space(line + 2);
	}
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
		if (nb == 6 + vars->door)
			break ;
		line = get_next_line(fd, 0);
	}
	if (vars->path->pn == 1 && vars->path->ps == 1
		&& vars->path->pw == 1 && vars->path->pe == 1
		&& vars->path->so == 1 && vars->path->pl == 1)
		vars = take_map2(fd, vars);
	else
	{
		line = get_next_line(fd, 1);
		free(line);
		vars->error = 2;
	}
	return (vars);
}
