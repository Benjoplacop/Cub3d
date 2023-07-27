/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:52:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/07/18 19:27:50 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	free_all_data(t_data *vars)
{
	int	i;

	i = -1;
	while (vars->map[++i])
		free(vars->map[i]);
	free(vars->path_north);
	free(vars->path_south);
	free(vars->path_west);
	free(vars->path_east);
	free(vars->sol);
	free(vars->plafond);
}

int destroy(t_data *vars)
{
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
