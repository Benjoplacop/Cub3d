/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 19:16:26 by bhennequ          #+#    #+#             */
/*   Updated: 2023/10/30 19:30:38 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	mouse_event(int x, int y, t_data *vars)
{
	(void)y;
	if (x < vars->position->centre_x)
		rotate_camera_left(vars);
	else if (x > vars->position->centre_x)
		rotate_camera_right(vars);
	mlx_mouse_move(vars->mlx, vars->win,
		vars->position->centre_x, vars->position->centre_y);
	return (1);
}

int	condition_map_close(int i, int j, t_data *vars)
{
	if (vars->map[i][j] == '0' || vars->map[i][j] == 'N'
			|| vars->map[i][j] == 'W' || vars->map[i][j] == 'S'
			|| vars->map[i][j] == 'E')
		return (1);
	return (0);
}

int	condition_carac_valid(char c, int door)
{
	if (door == 1 && (c != '0' && c != '1' && c != 'N'
			&& c != 'W' && c != 'E' && c != 'S'
			&& c != '\n' && c != '\0'
			&& c != ' ' && c != 'D'))
		return (1);
	else if (door == 0 && (c != '0' && c != '1' && c != 'N'
			&& c != 'W' && c != 'E' && c != 'S'
			&& c != '\n' && c != '\0'
			&& c != ' '))
		return (1);
	return (0);
}

void	open_door_cond(t_data *vars, int mapx, int mapy)
{
	if (vars->map[mapx][mapy] == 'd')
		vars->map[mapx][mapy] = 'D';
	else if (vars->map[mapx + 1][mapy] == 'd')
		vars->map[mapx + 1][mapy] = 'D';
	else if (vars->map[mapx][mapy + 1] == 'd')
		vars->map[mapx][mapy + 1] = 'D';
	else if (vars->map[mapx - 1][mapy] == 'd')
		vars->map[mapx - 1][mapy] = 'D';
	else if (vars->map[mapx][mapy - 1] == 'd')
		vars->map[mapx][mapy - 1] = 'D';
}
