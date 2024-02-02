/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_texture_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbilly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:09:44 by mbilly            #+#    #+#             */
/*   Updated: 2023/11/24 15:05:56 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*take_map3(t_data *vars)
{
	if (map_is_close(vars) == 1)
		fill_map(vars);
	else
		vars->error = 1;
	return (vars);
}

int	valid_texture_path2(t_data *vars)
{
	char	*tmp;
	int		tmp2;

	tmp = ft_strchr(&vars->path->path_east[1], '.');
	tmp2 = open(vars->path->path_east, O_RDONLY);
	if (!tmp || ft_strncmp(tmp, ".xpm\0", 5) != 0 || tmp2 == -1)
		return (0);
	close(tmp2);
	tmp = ft_strchr(&vars->path->path_west[1], '.');
	tmp2 = open(vars->path->path_west, O_RDONLY);
	if (!tmp || ft_strncmp(tmp, ".xpm\0", 5) != 0 || tmp2 == -1)
		return (0);
	close(tmp2);
	if (vars->door == 1)
	{
		tmp = ft_strchr(&vars->path->door[1], '.');
		tmp2 = open(vars->path->door, O_RDONLY);
		if (!tmp || ft_strncmp(tmp, ".xpm\0", 5) != 0 || tmp2 == -1)
			return (0);
		close(tmp2);
	}
	return (1);
}

int	valid_texture_path(t_data *vars)
{
	char	*tmp;
	int		tmp2;

	tmp = ft_strchr(&vars->path->path_north[1], '.');
	tmp2 = open(vars->path->path_north, O_RDONLY);
	if (!tmp || ft_strncmp(tmp, ".xpm\0", 5) != 0 || tmp2 == -1)
		return (0);
	close(tmp2);
	tmp = ft_strchr(&vars->path->path_south[1], '.');
	tmp2 = open(vars->path->path_south, O_RDONLY);
	if (!tmp || ft_strncmp(tmp, ".xpm\0", 5) != 0 || tmp2 == -1)
		return (0);
	close(tmp2);
	return (valid_texture_path2(vars));
}
