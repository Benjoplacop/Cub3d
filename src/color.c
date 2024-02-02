/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:41:49 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/22 13:54:07 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

void	test_color(char *texture, t_data *vars)
{
	char	**color;
	int		i;

	color = ft_split(texture, ',');
	i = -1;
	if (color[3])
	{
		vars->error = 1;
		while (color[++i])
			free(color[i]);
		free(color);
		return ;
	}
	if (ft_atoi(color[0]) > 255 || ft_atoi(color[1]) > 255
		|| ft_atoi(color[2]) > 255 || ft_atoi(color[0]) < 0
		|| ft_atoi(color[1]) < 0 || ft_atoi(color[2]) < 0)
		vars->error = 1;
	free(color[0]);
	free(color[1]);
	free(color[2]);
	free(color);
	return ;
}

int	transform_color(char *texture, t_data *vars)
{
	char			**color;
	int				r;
	int				g;
	int				b;
	unsigned int	hex_value;

	hex_value = 0;
	test_color(texture, vars);
	if (vars->error == 0)
	{
		color = ft_split(texture, ',');
		r = ft_atoi(color[0]);
		g = ft_atoi(color[1]);
		b = ft_atoi(color[2]);
		free(color[0]);
		free(color[1]);
		free(color[2]);
		free(color);
		hex_value = (r << 16) | (g << 8) | b;
	}
	return (hex_value);
}
