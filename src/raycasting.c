/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:40:21 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/09 17:12:04 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*raycasting_base(t_data *vars, int i)
{
	vars->position->cameraX = 2 * i / (double)WIDTH - 1;
	vars->position->raydirX = vars->position->dirX + vars->position->planeX * vars->position->cameraX;
	vars->position->raydirY = vars->position->dirY + vars->position->planeY * vars->position->cameraX;
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
	else if (vars->init_pos.dir == 'E')
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

t_data	*side_dist(t_data *vars)
{
	if (vars->position->raydirX < 0)
	{
		vars->position->stepX = -1;
		vars->position->sideDistX = (vars->position->x - vars->position->mapX) * vars->position->deltaDistX;
	}
	else
	{
		vars->position->stepX = 1;
		vars->position->sideDistX = (vars->position->mapX + 1 - vars->position->x) * vars->position->deltaDistX;
	}
	if (vars->position->raydirY < 0)
	{
		vars->position->stepY = -1;
		vars->position->sideDistY = (vars->position->y - vars->position->mapY) * vars->position->deltaDistY;
	}
	else
	{
		vars->position->stepY = 1;
		vars->position->sideDistY = (vars->position->mapY + 1 - vars->position->y) * vars->position->deltaDistY;
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

t_data	*wall_dist(t_data *vars)
{
	if (vars->position->side == 0)
		vars->position->perpWallDist = (vars->position->sideDistX - vars->position->deltaDistX);
	else
		vars->position->perpWallDist = (vars->position->sideDistY - vars->position->deltaDistY);
	vars->position->lineHeight = (int)(HEIGHT / vars->position->perpWallDist);	
	vars->position->drawStart = -vars->position->lineHeight / 2 + HEIGHT / 2;
	if (vars->position->drawStart < 0)
		vars->position->drawStart = 0;
	vars->position->drawEnd = vars->position->lineHeight / 2 + HEIGHT / 2;
	if (vars->position->drawEnd >= HEIGHT)
		vars->position->drawEnd = HEIGHT - 1;
	return (vars);
}

void	draw_image(t_data *vars, int i)
{
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		if (j >= vars->position->drawStart && j <= vars->position->drawEnd)
		{
			if (vars->position->side == 0)
					vars->color = 0xFF0000;
			else
					vars->color = 0x00FF00;
		}
		else
		{
			if (j < HEIGHT / 2)
				vars->color = transform_color(vars->path->sol);
			else
				vars->color = transform_color(vars->path->plafond);
		}
		my_mlx_pixel_put(vars, i, j, vars->color);
		j++;
	}
}

int	init_raycasting(t_data *vars)
{
	int	i;

	i = 0;
	vars = init_direction(vars);
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
	while (i < WIDTH)
	{
		vars = raycasting_base(vars, i);
		vars = side_dist(vars);
		vars = colision(vars);
		vars = wall_dist(vars);
		draw_image(vars, i);
		i++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}
