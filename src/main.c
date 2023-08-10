/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:38:55 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/10 12:14:11 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	good_arg(char **argv)
{
	int	i;

	i = 0;
	while (argv[1][i])
		i++;
	i--;
	if ((argv[1][i] != 'b' && argv[1][i - 1] != 'u'
		&& argv[1][i - 2] != 'c' && argv[1][i - 3] != '.') || i == 0)
	{
		ft_putstr_fd("Arguments need end by .cub\n", 1);
		return (0);
	}
	return (1);
}

t_data	*parse_link(t_data *vars)
{
	vars->path->sol[ft_strlen(vars->path->sol) - 1] = '\0';
	vars->path->plafond[ft_strlen(vars->path->plafond) - 1] = '\0';
	vars->path->path_north[ft_strlen(vars->path->path_north) - 1] = '\0';
	vars->path->path_south[ft_strlen(vars->path->path_south) - 1] = '\0';
	vars->path->path_west[ft_strlen(vars->path->path_west) - 1] = '\0';
	vars->path->path_east[ft_strlen(vars->path->path_east) - 1] = '\0';
	return (vars);
}

t_data	*init(t_data *vars, int fd)
{
	vars->error = 0;
	vars = take_map(fd, vars);
	vars = map_is_valid(vars);
	vars = parse_link(vars);
	vars->position->x = vars->init_pos.x + 0.5;
	vars->position->mapX = (int)vars->position->x;
	vars->position->y = vars->init_pos.y + 0.5;
	vars->position->mapY = (int)vars->position->y;
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
	vars->addr = mlx_get_data_addr(vars->img, &vars->bits_per_pixel, &vars->line_length, &vars->endian);
	mlx_hook(vars->win, 17, 1L << 0, &destroy, vars);
	mlx_key_hook(vars->win, key_utils, vars);
	mlx_loop_hook(vars->mlx, init_raycasting, vars);
	mlx_loop(vars->mlx);
}

int main(int argc, char **argv)
{
	t_data	*vars;
	int		fd;

	if (argc == 1 || good_arg(argv) == 0)
		return (1);
	vars = malloc(sizeof(t_data));
	vars->path = malloc(sizeof(t_path));
	vars->texture = malloc(sizeof(t_texture));
	vars->map = malloc(sizeof(char *) * (2065));
	vars->position = malloc(sizeof(t_position));
	if (!vars || !vars->path || !vars->texture || !vars->map || !vars->position)
		return (1);
	fd = open(argv[1], O_RDONLY);
	vars = init(vars, fd);
	if (vars->error != 0)
		printf("bad map\n");
		// return (1);
	init_mlx(vars);
	return (0);
}
