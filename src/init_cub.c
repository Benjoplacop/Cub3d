/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:49:00 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 16:03:39 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

char	*dup_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (ft_strdup(str + i));
}

int	good_arg(char **argv)
{
	char	*tmp;
	int		tmp2;

	tmp2 = open(argv[1], O_RDONLY);
	tmp = ft_strchr(argv[1], '.');
	if (!tmp || ft_strncmp(tmp, ".cub\0", 4) != 0 || tmp2 == -1)
	{
		ft_putstr_fd("Bad file input !\n", 2);
		return (0);
	}
	return (1);
}

void	load_texture_two(t_data *vars, t_texture *textures)
{
	textures[2].width = 750;
	textures[2].height = 1000;
	textures[2].img = mlx_xpm_file_to_image(vars->mlx,
			vars->path->path_south, &textures[2].width, &textures[2].height);
	textures[2].data = (int *)mlx_get_data_addr(textures[2].img,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	textures[3].width = 750;
	textures[3].height = 1000;
	textures[3].img = mlx_xpm_file_to_image(vars->mlx,
			vars->path->path_north, &textures[3].width, &textures[3].height);
	textures[3].data = (int *)mlx_get_data_addr(textures[3].img,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	if (vars->door == 1)
	{
		textures[4].width = 750;
		textures[4].height = 1000;
		textures[4].img = mlx_xpm_file_to_image(vars->mlx,
				vars->path->door, &textures[4].width, &textures[4].height);
		textures[4].data = (int *)mlx_get_data_addr(textures[4].img,
				&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	}
}

t_texture	*load_texture(t_data *vars)
{
	t_texture	*textures;

	textures = malloc(sizeof(t_texture) * 5);
	textures[0].width = 750;
	textures[0].height = 1000;
	textures[0].img = mlx_xpm_file_to_image(vars->mlx,
			vars->path->path_east, &textures[0].width, &textures[0].height);
	textures[0].data = (int *)mlx_get_data_addr(textures[0].img,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	textures[1].width = 750;
	textures[1].height = 1000;
	textures[1].img = mlx_xpm_file_to_image(vars->mlx,
			vars->path->path_west, &textures[1].width, &textures[1].height);
	textures[1].data = (int *)mlx_get_data_addr(textures[1].img,
			&vars->bits_per_pixel, &vars->line_length, &vars->endian);
	load_texture_two(vars, textures);
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
	if (vars->door == 1)
		vars->path->door[ft_strlen(vars->path->door) - 1] = '\0';
	if (valid_texture_path(vars) == 1)
		vars->texture = load_texture(vars);
	else
	{
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free_data_if_bad_map(vars);
		vars = NULL;
	}
	return (vars);
}
