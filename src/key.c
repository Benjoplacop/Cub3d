/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:10:59 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 14:42:35 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	move_forward(t_data *vars)
{
	int		mapx;
	int		mapy;
	double	new_posex;
	double	new_posey;

	new_posex = vars->position->x + vars->position->dirX * 0.1;
	new_posey = vars->position->y + vars->position->dirY * 0.1;
	mapx = (int)new_posex;
	mapy = (int)new_posey;
	if (vars->map[mapx][mapy] == '0')
	{
		vars->position->x = new_posex;
		vars->position->y = new_posey;
	}
	return (0);
}

int	move_backward(t_data *vars)
{
	int		mapx;
	int		mapy;
	double	new_posex;
	double	new_posey;

	new_posex = vars->position->x - vars->position->dirX * 0.1;
	new_posey = vars->position->y - vars->position->dirY * 0.1;
	mapx = (int)new_posex;
	mapy = (int)new_posey;
	if (vars->map[mapx][mapy] == '0')
	{
		vars->position->x = new_posex;
		vars->position->y = new_posey;
	}
	return (0);
}

int	move_key(int key, t_data *vars)
{
	if (key == 119)
		move_forward(vars);
	if (key == 97)
	{
		if (vars->position->dirX != 0)
			move_left(vars);
		else
			move_right(vars);
	}
	if (key == 115)
		move_backward(vars);
	if (key == 100)
	{
		if (vars->position->dirX != 0)
			move_right(vars);
		else
			move_left(vars);
	}
	return (0);
}

int	key_utils(int key, t_data *vars)
{
	if (key == XK_Escape)
		destroy(vars);
	if (key == 119 || key == 97 || key == 115 || key == 100)
		move_key(key, vars);
	if (key == 65361)
	{
		rotate_camera_left(vars);
	}
	if (key == 65363)
	{
		rotate_camera_right(vars);
	}
	return (1);
}
