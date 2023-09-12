/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:56:57 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 14:40:22 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	move_right(t_data *vars)
{
	double	new_posex;
	double	new_posey;
	int		mapx;
	int		mapy;

	new_posex = vars->position->x + -vars->position->dirY * 0.1;
	new_posey = vars->position->y + vars->position->dirX * 0.1;
	mapx = (int)new_posex;
	mapy = (int)new_posey;
	if (vars->map[mapx][mapy] == '0')
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

	new_posex = vars->position->x + vars->position->dirY * 0.1;
	new_posey = vars->position->y + -vars->position->dirX * 0.1;
	mapx = (int)new_posex;
	mapy = (int)new_posey;
	if (vars->map[mapx][mapy] == '0')
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

	rotspeed = 0.033 * 1.8;
	olddirx = vars->position->dirX;
	vars->position->dirX = vars->position->dirX * cos(rotspeed / 2)
		- vars->position->dirY * sin(rotspeed / 2);
	vars->position->dirY = olddirx * sin(rotspeed / 2)
		+ vars->position->dirY * cos(rotspeed / 2);
	oldplanex = vars->position->planeX;
	vars->position->planeX = vars->position->planeX * cos(rotspeed / 2)
		- vars->position->planeY * sin(rotspeed / 2);
	vars->position->planeY = oldplanex * sin(rotspeed / 2)
		+ vars->position->planeY * cos(rotspeed / 2);
	return (0);
}

int	rotate_camera_left(t_data *vars)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.033 * 1.8;
	olddirx = vars->position->dirX;
	vars->position->dirX = vars->position->dirX * cos(-rotspeed / 2)
		- vars->position->dirY * sin(-rotspeed / 2);
	vars->position->dirY = olddirx * sin(-rotspeed / 2)
		+ vars->position->dirY * cos(-rotspeed / 2);
	oldplanex = vars->position->planeX;
	vars->position->planeX = vars->position->planeX * cos(-rotspeed / 2)
		- vars->position->planeY * sin(-rotspeed / 2);
	vars->position->planeY = oldplanex * sin(-rotspeed / 2)
		+ vars->position->planeY * cos(-rotspeed / 2);
	return (0);
}
