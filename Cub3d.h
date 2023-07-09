/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:18:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/06/27 13:52:04 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

#include "libft/libft.h"
#include <stdio.h>
#include <fcntl.h>

# define BUFFER_SIZE 2064

typedef	struct	s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	char	*sol;
	char	*plafond;
	char	**map;
}				t_data;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

t_data  *take_map(int fd, t_data *vars);
char	*get_next_line(int fd);
int map_is_valid(t_data *vars);
#endif
