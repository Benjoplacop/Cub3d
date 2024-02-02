/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:38:55 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 15:48:06 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

t_data	*init_data(t_data *vars)
{
	vars->error = 0;
	vars->path->pn = 0;
	vars->path->ps = 0;
	vars->path->pw = 0;
	vars->path->pe = 0;
	vars->path->pl = 0;
	vars->path->so = 0;
	return (vars);
}

t_data	*init(t_data *vars, int fd)
{
	vars = init_data(vars);
	vars = take_map(fd, vars);
	vars = map_is_valid(vars);
	if (vars->path->pn != 1 || vars->path->ps != 1
		|| vars->path->pw != 1 || vars->path->pe != 1
		|| vars->path->so != 1 || vars->path->pl != 1)
		vars->error++;
	vars->color_sol = transform_color(vars->path->sol, vars);
	vars->color_plafond = transform_color(vars->path->plafond, vars);
	vars->position->x = vars->init_pos.x + 0.5;
	vars->position->mapx = (int)vars->position->x;
	vars->position->y = vars->init_pos.y + 0.5;
	vars->position->mapy = (int)vars->position->y;
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
	vars = init_direction(vars);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Hello World !");
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel,
			&vars->line_length, &vars->endian);
	vars = parse_link(vars);
	if (vars == NULL)
		return (ft_putstr_fd("Wrong texture path\n", 2));
	mlx_mouse_hide(vars->mlx, vars->win);
	mlx_hook(vars->win, 17, 1L << 0, &destroy, vars);
	mlx_key_hook(vars->win, key_utils, vars);
	mlx_loop_hook(vars->mlx, init_raycasting, vars);
	mlx_hook(vars->win, MotionNotify, PointerMotionMask, &mouse_event, vars);
	mlx_loop(vars->mlx);
}

int	main(int argc, char **argv)
{
	t_data	*vars;
	int		fd;

	if (argc != 2 || good_arg(argv) == 0)
		return (1);
	vars = malloc(sizeof(t_data));
	vars->path = malloc(sizeof(t_path));
	vars->position = malloc(sizeof(t_position));
	fd = open(argv[1], O_RDONLY);
	vars->door = 0;
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
