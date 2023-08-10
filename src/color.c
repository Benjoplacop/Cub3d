/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:41:49 by bhennequ          #+#    #+#             */
/*   Updated: 2023/08/09 15:48:52 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3d.h"

int	transform_color(char *texture)
{
	char			**color;
	int				r;
	int				g;
	int				b;
	unsigned int	hex_value;

	color = ft_split(texture, ',');
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	free(color[0]);
	free(color[1]);
	free(color[2]);
	free(color);
	hex_value = (r << 16) | (g << 8) | b;
	return (hex_value);
}
