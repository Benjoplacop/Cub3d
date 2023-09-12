/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:40:21 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 13:50:52 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*wall_dist(t_data *vars)
{
	if (vars->position->side == 0)
		vars->position->perpWallDist = (vars->position->sideDistX
				- vars->position->deltaDistX);
	else
		vars->position->perpWallDist = (vars->position->sideDistY
				- vars->position->deltaDistY);
	vars->position->lineHeight = (int)(HEIGHT / vars->position->perpWallDist);
	vars->position->drawStart = -vars->position->lineHeight / 2 + HEIGHT / 2;
	if (vars->position->drawStart < 0)
		vars->position->drawStart = 0;
	vars->position->drawEnd = vars->position->lineHeight / 2 + HEIGHT / 2;
	if (vars->position->drawEnd >= HEIGHT)
		vars->position->drawEnd = HEIGHT - 1;
	return (vars);
}

t_data	*calcul_text(t_data *vars, int tex_num, int j)
{
	int		tex_width;
	int		tex_height;
	double	wall_x;

	tex_width = vars->texture[tex_num].width;
	tex_height = vars->texture[tex_num].height;
	if (vars->position->side == 0)
		wall_x = vars->position->y + vars->position->perpWallDist
			* vars->position->raydirY;
	else
		wall_x = vars->position->x + vars->position->perpWallDist
			* vars->position->raydirX;
	wall_x -= floor(wall_x);
	vars->position->texX = (int)(wall_x * (double)tex_width);
	vars->position->texY = ((((j - HEIGHT / 2 + vars->position->lineHeight / 2)
					* tex_height) / vars->position->lineHeight) % tex_height);
	return (vars);
}

t_data	*draw_text(t_data *vars, int j)
{
	int	tex_num;

	if (vars->position->side == 0)
	{
		if (vars->position->raydirX > 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	else
	{
		if (vars->position->raydirY > 0)
			tex_num = 1;
		else
			tex_num = 0;
	}
	vars = calcul_text(vars, tex_num, j);
	vars->color = vars->texture[tex_num].data[vars->position->texY
		* vars->texture[tex_num].width + vars->position->texX];
	return (vars);
}

void	draw_image(t_data *vars, int i)
{
	int	j;
	int	sol;
	int	plafond;

	sol = transform_color(vars->path->sol);
	plafond = transform_color(vars->path->plafond);
	j = 0;
	while (j < HEIGHT)
	{
		if (j >= vars->position->drawStart && j <= vars->position->drawEnd)
			vars = draw_text(vars, j);
		else
		{
			if (j < HEIGHT / 2)
				vars->color = sol;
			else
				vars->color = plafond;
		}
		my_mlx_pixel_put(vars, i, j, vars->color);
		j++;
	}
}

int	init_raycasting(t_data *vars)
{
	int	i;

	i = 0;
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
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
