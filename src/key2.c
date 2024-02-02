/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:56:57 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 13:17:50 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	move_right(t_data *vars)
{
	double	new_posex;
	double	new_posey;
	int		mapx;
	int		mapy;

	new_posex = vars->position->x + vars->position->diry * 0.1;
	new_posey = vars->position->y + vars->position->dirx * 0.1;
	mapx = (int)new_posex;
	mapy = (int)new_posey;
	if (vars->map[mapx][mapy] == '0' || vars->map[mapx][mapy] == 'd')
	{
		vars->position->x = new_posex;
		vars->position->y = new_posey;
	}
	return (0);
}

int	move_left(t_data *vars)
{
	double	new_posex;
	double	new_posey;
	int		mapx;
	int		mapy;

	new_posex = vars->position->x - vars->position->diry * 0.1;
	new_posey = vars->position->y - vars->position->dirx * 0.1;
	mapx = (int)new_posex;
	mapy = (int)new_posey;
	if (vars->map[mapx][mapy] == '0' || vars->map[mapx][mapy] == 'd')
	{
		vars->position->x = new_posex;
		vars->position->y = new_posey;
	}
	return (0);
}

int	rotate_camera_right(t_data *vars)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.033 * 1.05;
	olddirx = vars->position->dirx;
	vars->position->dirx = vars->position->dirx * cos(rotspeed / 2)
		- vars->position->diry * sin(rotspeed / 2);
	vars->position->diry = olddirx * sin(rotspeed / 2)
		+ vars->position->diry * cos(rotspeed / 2);
	oldplanex = vars->position->planex;
	vars->position->planex = vars->position->planex * cos(rotspeed / 2)
		- vars->position->planey * sin(rotspeed / 2);
	vars->position->planey = oldplanex * sin(rotspeed / 2)
		+ vars->position->planey * cos(rotspeed / 2);
	return (0);
}

int	rotate_camera_left(t_data *vars)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.033 * 1.05;
	olddirx = vars->position->dirx;
	vars->position->dirx = vars->position->dirx * cos(-rotspeed / 2)
		- vars->position->diry * sin(-rotspeed / 2);
	vars->position->diry = olddirx * sin(-rotspeed / 2)
		+ vars->position->diry * cos(-rotspeed / 2);
	oldplanex = vars->position->planex;
	vars->position->planex = vars->position->planex * cos(-rotspeed / 2)
		- vars->position->planey * sin(-rotspeed / 2);
	vars->position->planey = oldplanex * sin(-rotspeed / 2)
		+ vars->position->planey * cos(-rotspeed / 2);
	return (0);
}
