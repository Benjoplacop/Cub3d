/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:38:55 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 14:49:06 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*init(t_data *vars, int fd)
{
	vars->error = 0;
	vars = take_map(fd, vars);
	vars = map_is_valid(vars);
	vars->position->x = vars->init_pos.x + 0.5;
	vars->position->mapX = (int)vars->position->x;
	vars->position->y = vars->init_pos.y + 0.5;
	vars->position->mapY = (int)vars->position->y;
	vars = init_direction(vars);
	return (vars);
}

void	my_mlx_pixel_put(t_data *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->addr + (y * vars->line_length + x * (vars->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx(t_data *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Hello World !");
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
	vars = parse_link(vars);
	mlx_hook(vars->win, 17, 1L << 0, &destroy, vars);
	mlx_key_hook(vars->win, key_utils, vars);
	mlx_loop_hook(vars->mlx, init_raycasting, vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char **argv)
{
	t_data	*vars;
	int		fd;

	if (argc == 1 || good_arg(argv) == 0)
		return (1);
	vars = malloc(sizeof(t_data));
	vars->path = malloc(sizeof(t_path));
	vars->position = malloc(sizeof(t_position));
	fd = open(argv[1], O_RDONLY);
	vars = take_map_size(fd, vars);
	close(fd);
	if (!vars || !vars->path || !vars->position)
		return (1);
	fd = open(argv[1], O_RDONLY);
	vars = init(vars, fd);
	if (vars->error != 0)
	{
		free_data_if_bad_map(vars);
		printf("Bad map\n");
		return (1);
	}
	close(fd);
	init_mlx(vars);
	return (0);
}
