/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:38:14 by bhennequ          #+#    #+#             */
/*   Updated: 2023/10/31 12:42:16 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	my_mlx_pixel_put2(t_data *vars, int x, int y, unsigned int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_square(t_data *vars)
{
	int	i;
	int	j;
	int	width;
	int	height;

	width = (WIDTH / 7) + 10;
	height = (HEIGHT / 7) + 10;
	i = 0;
	j = 0;
	while (i < width)
	{
		while (j < height)
		{
			if (j % 2 == 0)
				my_mlx_pixel_put2(vars, i, j, 0x696969);
			j++;
		}
		j = 0;
		i++;
	}
}

void	draw_wall(t_data *vars, int i, int j, unsigned int color)
{
	int	i2;
	int	j2;
	int	i_max;
	int	j_max;

	i_max = i * 7 + 7;
	j_max = j * 6 + 7;
	i2 = i * 7;
	j2 = j * 6;
	while (i2 < i_max)
	{
		while (j2 < j_max)
		{
			my_mlx_pixel_put2(vars, j2 + 5, i2 + 5, color);
			j2++;
		}
		j2 = j * 6;
		i2++;
	}
}

void	draw_character(t_data *vars, int i, int j)
{
	int	i2;
	int	j2;
	int	j2_save;
	int	i_max;
	int	j_max;

	i_max = i * 7 + 5;
	j_max = j * 6 + 5;
	i2 = i * 7;
	j2_save = j * 6;
	while (i2 < i_max)
	{
		j2 = j2_save;
		while (j2 < j_max)
		{
			my_mlx_pixel_put2(vars, j2 + 5, i2 + 5, 0x0000FF);
			j2++;
		}
		i2++;
	}
}

void	draw_minimap(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	draw_square(vars);
	while (vars->map[i])
	{
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '1')
				draw_wall(vars, i, j, 0xFF0000);
			else if (vars->map[i][j] == 'D' || vars->map[i][j] == 'd')
				draw_wall(vars, i, j, 0x582900);
			j++;
		}
		j = 0;
		i++;
	}
	draw_character(vars, vars->position->x, vars->position->y);
}
