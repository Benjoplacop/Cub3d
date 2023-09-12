/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:49:00 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 15:03:41 by bhennequ         ###   ########.fr       */
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

t_texture	*load_texture(t_data *vars)
{
	int			i;
	t_texture	*textures;

	i = 0;
	textures = malloc(sizeof(t_texture) * 4);
	while (i < 4)
	{
		textures[i].width = 750;
		textures[i].height = 1000;
		textures[i].img = mlx_xpm_file_to_image(vars->mlx,
				vars->path->path_north, &textures[i].width,
				&textures[i].height);
		textures[i].data = (int *)mlx_get_data_addr(textures[i].img,
				&vars->bits_per_pixel, &vars->line_length, &vars->endian);
		i++;
	}
	return (textures);
}

t_data	*parse_link(t_data *vars)
{
	vars->path->sol[ft_strlen(vars->path->sol) - 1] = '\0';
	vars->path->plafond[ft_strlen(vars->path->plafond) - 1] = '\0';
	vars->path->path_north[ft_strlen(vars->path->path_north) - 1] = '\0';
	vars->path->path_south[ft_strlen(vars->path->path_south) - 1] = '\0';
	vars->path->path_west[ft_strlen(vars->path->path_west) - 1] = '\0';
	vars->path->path_east[ft_strlen(vars->path->path_east) - 1] = '\0';
	vars->texture = load_texture(vars);
	return (vars);
}
