/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:30:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 13:21:21 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*raycasting_base(t_data *vars, int i)
{
	vars->position->camerax = 2 * i / (double)WIDTH - 1;
	vars->position->raydirx = vars->position->dirx
		+ vars->position->planex * vars->position->camerax;
	vars->position->raydiry = vars->position->diry
		+ vars->position->planey * vars->position->camerax;
	vars->position->mapx = (int)vars->position->x;
	vars->position->mapy = (int)vars->position->y;
	if (vars->position->raydirx == 0)
		vars->position->deltadistx = 1e30;
	else
		vars->position->deltadistx = fabs(1 / vars->position->raydirx);
	if (vars->position->raydiry == 0)
		vars->position->deltadisty = 1e30;
	else
		vars->position->deltadisty = fabs(1 / vars->position->raydiry);
	return (vars);
}

t_data	*init_direction_two(t_data *vars)
{
	if (vars->init_pos.dir == 'E')
	{
		vars->position->dirx = 0;
		vars->position->diry = -1;
		vars->position->planex = 0.66;
		vars->position->planey = 0;
	}
	else
	{
		vars->position->dirx = 1;
		vars->position->diry = 0;
		vars->position->planex = 0;
		vars->position->planey = 0.66;
	}
	return (vars);
}

t_data	*init_direction(t_data *vars)
{
	vars->position->centre_x = WIDTH / 2;
	vars->position->centre_y = HEIGHT / 2;
	if (vars->init_pos.dir == 'N')
	{
		vars->position->dirx = -1;
		vars->position->diry = 0;
		vars->position->planex = 0;
		vars->position->planey = -0.66;
	}
	else if (vars->init_pos.dir == 'W')
	{
		vars->position->dirx = 0;
		vars->position->diry = 1;
		vars->position->planex = -0.66;
		vars->position->planey = 0;
	}
	else
		vars = init_direction_two(vars);
	return (vars);
}

t_data	*side_dist(t_data *vars)
{
	if (vars->position->raydirx > 0)
	{
		vars->position->stepx = -1;
		vars->position->sidedistx = (vars->position->x
				- vars->position->mapx) * vars->position->deltadistx;
	}
	else
	{
		vars->position->stepx = 1;
		vars->position->sidedistx = (vars->position->mapx + 1
				- vars->position->x) * vars->position->deltadistx;
	}
	if (vars->position->raydiry < 0)
	{
		vars->position->stepy = -1;
		vars->position->sidedisty = (vars->position->y
				- vars->position->mapy) * vars->position->deltadisty;
	}
	else
	{
		vars->position->stepy = 1;
		vars->position->sidedisty = (vars->position->mapy + 1
				- vars->position->y) * vars->position->deltadisty;
	}
	return (vars);
}

t_data	*colision(t_data *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->position->sidedistx < vars->position->sidedisty)
		{
			vars->position->sidedistx += vars->position->deltadistx;
			vars->position->mapx += vars->position->stepx;
			vars->position->side = 0;
		}
		else
		{
			vars->position->sidedisty += vars->position->deltadisty;
			vars->position->mapy += vars->position->stepy;
			vars->position->side = 1;
		}
		if (vars->map[vars->position->mapx][vars->position->mapy] != '0' &&
				vars->map[vars->position->mapx][vars->position->mapy] != 'd')
			hit = 1;
	}
	return (vars);
}
