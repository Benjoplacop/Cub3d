/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:38:55 by bhennequ          #+#    #+#             */
/*   Updated: 2023/07/21 20:47:11 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	free_all_data(t_data *vars)
{
	int	i;

	i = -1;
	free(vars->mlx);
	free(vars->path_south);
	free(vars->path_north);
	free(vars->path_west);
	free(vars->path_east);
	free(vars->sol);
	free(vars->plafond);
	while (vars->map[++i])
		free(vars->map[i]);
}

int destroy(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free_all_data(data);
	exit(0);
	return (0);
}

int main(int argc, char **argv)
{
	t_data	*vars;
	int		fd;

	(void) argc;
	vars = malloc(sizeof(t_data));
	fd = open(argv[1], O_RDONLY);
	vars->map = malloc(sizeof(char) * (2065));
	vars = take_map(fd, vars);
	if (map_is_valid(vars) == 0)
		printf("Bad map\n");
	return (0);
}
