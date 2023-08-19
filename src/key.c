/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:10:59 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/16 16:20:24 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	move_right(t_data *vars)
{
	double	left_x;
	double	left_y;
	double	new_posex;
	double	new_posey;
	int		mapx;
	int		mapy;

	left_x = -vars->position->dirY;
	left_y = vars->position->dirX;
	new_posex = vars->position->x + left_x * 0.1;
	new_posey = vars->position->y + left_y * 0.1;
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
	double	right_x;
	double	right_y;
	double	new_posex;
	double	new_posey;
	int		mapx;
	int		mapy;

	right_x = vars->position->dirY;
	right_y = -vars->position->dirX;
    new_posex = vars->position->x + right_x * 0.1;
    new_posey = vars->position->y + right_y * 0.1;
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
	vars->position->dirX = vars->position->dirX * cos(rotspeed / 2) - vars->position->dirY * sin(rotspeed / 2);
	vars->position->dirY = olddirx * sin(rotspeed / 2) + vars->position->dirY * cos(rotspeed / 2);
	oldplanex = vars->position->planeX;
	vars->position->planeX = vars->position->planeX * cos(rotspeed / 2) - vars->position->planeY * sin(rotspeed / 2);
	vars->position->planeY = oldplanex * sin(rotspeed / 2) + vars->position->planeY * cos(rotspeed / 2);
	return (0);
}

int	rotate_camera_left(t_data *vars)
{
	double	rotspeed;
	double	olddirx;
	double	oldplanex;

	rotspeed = 0.033 * 1.8;
	olddirx = vars->position->dirX;
	vars->position->dirX = vars->position->dirX * cos(-rotspeed / 2) - vars->position->dirY * sin(-rotspeed / 2);
	vars->position->dirY = olddirx * sin(-rotspeed / 2) + vars->position->dirY * cos(-rotspeed / 2);
	oldplanex = vars->position->planeX;
	vars->position->planeX = vars->position->planeX * cos(-rotspeed / 2) - vars->position->planeY * sin(-rotspeed / 2);
	vars->position->planeY = oldplanex * sin(-rotspeed / 2) + vars->position->planeY * cos(-rotspeed / 2);
	return (0);
}

int	move_forward(t_data *vars)
{
	int		mapX;
	int		mapY;
	double	new_poseX;
	double	new_poseY;

	new_poseX = vars->position->x + vars->position->dirX * 0.1;
	new_poseY = vars->position->y + vars->position->dirY * 0.1;
	mapX = (int)new_poseX;
	mapY = (int)new_poseY;
	if (vars->map[mapX][mapY] == '0')
	{
		vars->position->x = new_poseX;
		vars->position->y = new_poseY;
	}
	return (0);
}

int	move_backward(t_data *vars)
{
	int		mapX;
	int		mapY;
	double	new_poseX;
	double	new_poseY;

	new_poseX = vars->position->x - vars->position->dirX * 0.1;
	new_poseY = vars->position->y - vars->position->dirY * 0.1;
	mapX = (int)new_poseX;
	mapY = (int)new_poseY;
	if (vars->map[mapX][mapY] == '0')
	{
		vars->position->x = new_poseX;
		vars->position->y = new_poseY;
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
//	printf("%i\n", key);
	return (1);
}
