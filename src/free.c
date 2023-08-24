/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:52:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/24 14:29:07 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	free_all_data(t_data *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		free(vars->map[i]);
		i++;
	}
	free(vars->map);
	free(vars->path->path_north);
	free(vars->path->path_south);
	free(vars->path->path_west);
	free(vars->path->path_east);
	free(vars->path->sol);
	free(vars->path->plafond);
	free(vars->texture);
	free(vars->path);
	free(vars->position);
}

int	destroy(t_data *vars)
{
	mlx_destroy_image(vars->mlx, vars->texture[0].img);
	mlx_destroy_image(vars->mlx, vars->texture[1].img);
	mlx_destroy_image(vars->mlx, vars->texture[2].img);
	mlx_destroy_image(vars->mlx, vars->texture[3].img);
	mlx_destroy_image(vars->mlx, vars->img);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	mlx_loop_end(vars->mlx);
	free_all_data(vars);
	free(vars->mlx);
	free(vars);
	exit(0);
	return (0);
}
