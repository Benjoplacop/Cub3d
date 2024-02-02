/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:05:43 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 13:22:21 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

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
			if (condition_carac_valid(c, vars->door))
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

t_data	*take_init_pos(t_data *vars, int i, int j)
{
	vars->init_pos.x = i;
	vars->init_pos.y = j;
	vars->init_pos.dir = vars->map[i][j];
	if (vars->init_pos.dir == 'N')
		vars->init_pos.dir = 'S';
	else if (vars->init_pos.dir == 'S')
		vars->init_pos.dir = 'N';
	else if (vars->init_pos.dir == 'W')
		vars->init_pos.dir = 'E';
	else
		vars->init_pos.dir = 'W';
	vars->map[i][j] = '0';
	return (vars);
}

t_data	*position_init(t_data *vars)
{
	int		i;
	int		j;
	int		spawn;

	spawn = 0;
	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'E'
				|| vars->map[i][j] == 'W' || vars->map[i][j] == 'S')
			{
				spawn++;
				vars = take_init_pos(vars, i, j);
			}
			j++;
		}
		i++;
	}
	if (spawn != 1)
		vars->error = 1;
	return (vars);
}

int	map_is_long(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (ft_strncmp(vars->map[i], "\n\0", 2) == 0
				&& !ft_strchr("\n\0", vars->map[i + 1][0]))
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

	if (map_is_long(vars) == 0 || jsp(vars) == 0)
		return (0);
	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (condition_map_close(i, j, vars))
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
