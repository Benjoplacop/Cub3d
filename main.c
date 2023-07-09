/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:38:55 by bhennequ          #+#    #+#             */
/*   Updated: 2023/06/27 13:50:26 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

/*int destroy(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
	return (0);
}*/

int main(int argc, char **argv)
{
	t_data	*vars;
	int		fd;

	(void) argc;
	vars = malloc(sizeof(t_data));
	fd = open(argv[1], O_RDONLY);
	vars->map = malloc(sizeof(char) * (2065));
	vars = take_map(fd, vars);
	int	i = 0;
	while (vars->map[i])
	{
		printf("%s", vars->map[i]);
		i++;
	}
	if (map_is_valid(vars) == 0)
		return (1);
//	mlx_key_hook(vars->win, key_utils, vars);
//	mlx_hook(vars->win, 17, 1L << 0, &destroy, vars);
	return (0);
}
