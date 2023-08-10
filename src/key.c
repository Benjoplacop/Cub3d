/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 16:10:59 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/10 12:04:59 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	move_right(t_data *vars)
{
	double	old_dir_x;
	double	old_plane_x;
	double	left_x;
	double	left_y;

	old_dir_x = vars->position->dirX;
	vars->position->dirX = vars->position->dirX * cos(0.1) - vars->position->dirY * sin(0.1);
	vars->position->dirY = old_dir_x * sin(0.1) + vars->position->dirY * cos(0.1);
	old_plane_x = vars->position->planeX;
	vars->position->planeX = vars->position->planeX * cos(0.1) - vars->position->planeY * sin(0.1);
	vars->position->planeY = old_plane_x * sin(0.1) + vars->position->planeY * cos(0.1);
	left_x = -vars->position->dirY;
	left_y = vars->position->dirX;
	vars->position->x += left_x * 0.25;
	vars->position->y += left_y * 0.25;
	return (0);
}

int	move_left(t_data *vars)
{
	double	old_dir_x;
	double	old_plane_x;
	double	right_x;
	double	right_y;

	old_dir_x = vars->position->dirX;
	vars->position->dirX = vars->position->dirX * cos(-0.1) - vars->position->dirY * sin(-0.1);
	vars->position->dirY = old_dir_x * sin(-0.1) + vars->position->dirY * cos(-0.1);
	old_plane_x = vars->position->planeX;
    vars->position->planeX = vars->position->planeX * cos(-0.1) - vars->position->planeY * sin(-0.1);
    vars->position->planeY = old_plane_x * sin(-0.1) + vars->position->planeY * cos(-0.1);
	right_x = vars->position->dirY;
	right_y = -vars->position->dirX;
    vars->position->x += right_x * 0.25;
    vars->position->y += right_y * 0.25;
	return (0);
}

int	move_key(int key, t_data *vars)
{
	if (key == 119)
	{
		vars->position->x += vars->position->dirX * 0.25;
        vars->position->y += vars->position->dirY * 0.25;
	}
	if (key == 97)
	{
		if (vars->position->dirX != 0)
			move_left(vars);
		else
			move_right(vars);
	}
	if (key == 115)
	{
		vars->position->x -= vars->position->dirX * 0.25;
        vars->position->y -= vars->position->dirY * 0.25;
	}
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
//	if (key == 65361)
//	{
//	}
//	if (key == 65363)
//	{
//	}
//	printf("%i\n", key);
	return (1);
}
