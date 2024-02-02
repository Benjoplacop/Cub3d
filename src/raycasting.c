/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:40:21 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/20 10:57:06 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*wall_dist(t_data *vars)
{
	if (vars->position->side == 0)
		vars->position->perpwalldist = (vars->position->sidedistx
				- vars->position->deltadistx);
	else
		vars->position->perpwalldist = (vars->position->sidedisty
				- vars->position->deltadisty);
	vars->position->lineheight = (int)(HEIGHT / vars->position->perpwalldist);
	vars->position->drawstart = -vars->position->lineheight / 2 + HEIGHT / 2;
	if (vars->position->drawstart < 0)
		vars->position->drawstart = 0;
	vars->position->drawend = vars->position->lineheight / 2 + HEIGHT / 2;
	if (vars->position->drawend >= HEIGHT)
		vars->position->drawend = HEIGHT - 1;
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
		wall_x = vars->position->y + vars->position->perpwalldist
			* vars->position->raydiry;
	else
		wall_x = vars->position->x + vars->position->perpwalldist
			* vars->position->raydirx;
	wall_x -= floor(wall_x);
	vars->position->texx = (int)(wall_x * (double)tex_width);
	vars->position->texy = ((((j - HEIGHT / 2 + vars->position->lineheight / 2)
					* tex_height) / vars->position->lineheight) % tex_height);
	return (vars);
}

t_data	*draw_text(t_data *vars, int j)
{
	int	tex_num;

	if (vars->position->side == 0)
	{
		if (vars->position->raydirx > 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	else
	{
		if (vars->position->raydiry > 0)
			tex_num = 1;
		else
			tex_num = 0;
	}
	if (vars->map[vars->position->mapx][vars->position->mapy] == 'D')
		tex_num = 4;
	if (vars->map[vars->position->mapx][vars->position->mapy] == 'd')
		return (vars);
	vars = calcul_text(vars, tex_num, j);
	vars->color = vars->texture[tex_num].data[vars->position->texy
		* vars->texture[tex_num].width + vars->position->texx];
	return (vars);
}

void	draw_image(t_data *vars, int i)
{
	int	j;

	j = 0;
	while (j < HEIGHT)
	{
		if (j >= vars->position->drawstart && j <= vars->position->drawend)
			vars = draw_text(vars, j);
		else
		{
			if (j < HEIGHT / 2)
				vars->color = vars->color_sol;
			else
				vars->color = vars->color_plafond;
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
	draw_minimap(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	return (0);
}
