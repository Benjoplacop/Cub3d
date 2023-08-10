/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:52:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/10 11:37:51 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	free_all_data(t_data *vars)
{
	int	i;

	i = -1;
	while (vars->map[++i])
		free(vars->map[i]);
	free(vars->path->path_north);
	free(vars->path->path_south);
	free(vars->path->path_west);
	free(vars->path->path_east);
	free(vars->path->sol);
	free(vars->path->plafond);
}

int	destroy(t_data *vars)
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
