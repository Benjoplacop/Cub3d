/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:49:28 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 15:52:47 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*replace_void(t_data *vars, char *line, int i, int j)
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
	return (vars);
}

void	fill_map(t_data *vars)
{
	int		i;
	int		j;
	char	*line;

	line = malloc(sizeof(char) * (vars->size_line + 1));
	if (!line)
		return ;
	i = 0;
	j = 0;
	while (vars->map[i])
	{
		replace_void(vars, line, i, j);
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

t_data	*map_is_valid(t_data *vars)
{
	if (vars->error == 0)
	{
		vars = carac_is_valid(vars);
		vars = position_init(vars);
	}
	else
	{
		if (vars->error == 1)
			free_data_if_bad_map(vars);
		else
			free_data_if_bad_map2(vars);
		ft_putstr_fd("bad map\n", 1);
		exit(1);
	}
	return (vars);
}
