/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:18:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/07/18 19:03:26 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# define WIDTH 1920
# define HEIGTH 1080

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef	struct	s_data
{
	void	*mlx;
	void	*mlx_pointer;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	char	*sol;
	char	*plafond;
	char	**map;
	int		size_line;
	int		error;
	t_point	init_pos;
}				t_data;

int destroy(t_data *vars);
void    free_all_data(t_data *vars);
int map_is_close(t_data *vars);
t_data  *take_map(int fd, t_data *vars);
char	*get_next_line(int fd);
t_data *map_is_valid(t_data *vars);
#endif
