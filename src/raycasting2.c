/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:30:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 14:55:47 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*raycasting_base(t_data *vars, int i)
{
	vars->position->cameraX = 2 * i / (double)WIDTH - 1;
	vars->position->raydirX = vars->position->dirX
		+ vars->position->planeX * vars->position->cameraX;
	vars->position->raydirY = vars->position->dirY
		+ vars->position->planeY * vars->position->cameraX;
	vars->position->mapX = (int)vars->position->x;
	vars->position->mapY = (int)vars->position->y;
	if (vars->position->raydirX == 0)
		vars->position->deltaDistX = 1e30;
	else
		vars->position->deltaDistX = fabs(1 / vars->position->raydirX);
	if (vars->position->raydirX == 0)
		vars->position->deltaDistY = 1e30;
	else
		vars->position->deltaDistY = fabs(1 / vars->position->raydirY);
	return (vars);
}

t_data	*init_direction_two(t_data *vars)
{
	if (vars->init_pos.dir == 'E')
	{
		vars->position->dirX = 0;
		vars->position->dirY = 1;
		vars->position->planeX = 0.66;
		vars->position->planeY = 0;
	}
	else
	{
		vars->position->dirX = 1;
		vars->position->dirY = 0;
		vars->position->planeX = 0;
		vars->position->planeY = 0.66;
	}
	return (vars);
}

t_data	*init_direction(t_data *vars)
{
	if (vars->init_pos.dir == 'N')
	{
		vars->position->dirX = -1;
		vars->position->dirY = 0;
		vars->position->planeX = 0;
		vars->position->planeY = -0.66;
	}
	else if (vars->init_pos.dir == 'W')
	{
		vars->position->dirX = 0;
		vars->position->dirY = -1;
		vars->position->planeX = -0.66;
		vars->position->planeY = 0;
	}
	else
		vars = init_direction_two(vars);
	return (vars);
}

t_data	*side_dist(t_data *vars)
{
	if (vars->position->raydirX < 0)
	{
		vars->position->stepX = -1;
		vars->position->sideDistX = (vars->position->x
				- vars->position->mapX) * vars->position->deltaDistX;
	}
	else
	{
		vars->position->stepX = 1;
		vars->position->sideDistX = (vars->position->mapX + 1
				- vars->position->x) * vars->position->deltaDistX;
	}
	if (vars->position->raydirY < 0)
	{
		vars->position->stepY = -1;
		vars->position->sideDistY = (vars->position->y
				- vars->position->mapY) * vars->position->deltaDistY;
	}
	else
	{
		vars->position->stepY = 1;
		vars->position->sideDistY = (vars->position->mapY + 1
				- vars->position->y) * vars->position->deltaDistY;
	}
	return (vars);
}

t_data	*colision(t_data *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->position->sideDistX < vars->position->sideDistY)
		{
			vars->position->sideDistX += vars->position->deltaDistX;
			vars->position->mapX += vars->position->stepX;
			vars->position->side = 0;
		}
		else
		{
			vars->position->sideDistY += vars->position->deltaDistY;
			vars->position->mapY += vars->position->stepY;
			vars->position->side = 1;
		}
		if (vars->map[vars->position->mapX][vars->position->mapY] > '0')
			hit = 1;
	}
	return (vars);
}
