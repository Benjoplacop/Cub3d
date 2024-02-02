/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 18:52:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 15:43:30 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	free_data_if_bad_map2(t_data *vars)
{
	if (vars->path->pn)
		free(vars->path->path_north);
	if (vars->path->ps)
		free(vars->path->path_south);
	if (vars->path->pe)
		free(vars->path->path_east);
	if (vars->path->pw)
		free(vars->path->path_west);
	if (vars->path->so)
		free(vars->path->sol);
	if (vars->path->pl)
		free(vars->path->plafond);
	if (vars->door)
		free(vars->path->door);
	free(vars->path);
	free(vars->position);
	free(vars->map);
	free(vars);
}

void	free_data_if_bad_map(t_data *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		free(vars->map[i]);
		i++;
	}
	free_data_if_bad_map2(vars);
}

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
	if (vars->door)
		free(vars->path->door);
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
	if (vars->door)
		mlx_destroy_image(vars->mlx, vars->texture[4].img);
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

int	jsp(t_data *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->map[i])
		i++;
	i--;
	while (vars->map[i][j] != '\n' && vars->map[i][j])
	{
		if (vars->map[i][j] != '1')
			return (0);
		j++;
	}
	return (1);
}
