/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 12:38:55 by bhennequ          #+#    #+#             */
/*   Updated: 2023/07/18 19:27:13 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

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

void	init_mlx(t_data *vars)
{
//	void	*image_ptr;
//	char	*img_data;
//	int		size_line;
//	int		endian;
//
//	endian = 0;
//	size_line = 7680;
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGTH, "Hello World !");
//	image_ptr = mlx_new_image(vars->mlx_pointer, WIDTH, HEIGTH);
//	img_data = mlx_get_data_addr(image_ptr, &vars->bit_per_pixel, &size_line, &endian);
	mlx_hook(vars->win, 17, 1L << 0, &destroy, vars);
	mlx_loop(vars->mlx);
}

int main(int argc, char **argv)
{
	t_data	*vars;
	int		fd;

	if (argc == 1 || good_arg(argv) == 0)
		return (1);
//	if ((fd = open(argv[1], O_DIRECTORY)) != -1 || (fd = open(argv[1], O_RDONLY)) == -1)
//	{	
//		if ((fd = open(argv[1], O_RDONLY)) == -1)
//			ft_putstr_fd("Fichier .cub invalide\n", 1);
//		else
//			ft_putstr_fd("Invalide : is a directory\n", 1);
//		return (0);
//	}
	vars = malloc(sizeof(t_data));
	fd = open(argv[1], O_RDONLY);
	vars->map = malloc(sizeof(char) * (2065));
	vars->error = 0;
	vars = take_map(fd, vars);
	vars = map_is_valid(vars);
	if (vars->error != 0)
		printf("bad map\n");
		// return (1);
	// ce qui se passe avant: recuperation de la map + test si tout fonctionne
	// la suite: initialisation de la minilibx
	init_mlx(vars);
	return (0);
}
