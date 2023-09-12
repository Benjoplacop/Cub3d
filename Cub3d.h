/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:18:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/09/12 15:15:21 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D
# define CUB3D

# define WIDTH 1920
# define HEIGHT 1080
# define BUFFER_SIZE 1024

# include <math.h>
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

typedef struct	s_point
{
	int		x;
	int		y;
	char	dir;
}				t_point;

typedef struct	s_path
{
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	char	*sol;
	char	*plafond;
}				t_path;

typedef	struct	s_position
{
	double	x;
	double	y;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	raydirX;
	double	raydirY;
	double	cameraX;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	int		texY;
	int		texX;
	int		side;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}				t_position;

typedef	struct	s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		line_length;
}				t_texture;

typedef	struct	s_data
{
	void	*mlx;
	void	*mlx_pointer;
	void	*win;
	void	*img;
	void	*addr;
	int		endian;
	int		color;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		img_width;
	int		img_heigth;
	char	**map;
	int		size_line;
	int		size_map;
	int		error;
	t_path		*path;
	t_texture	*texture;
	t_point		init_pos;
	t_position	*position;
}				t_data;

t_data		*carac_is_valid(t_data *vars);
t_data		*position_init(t_data *vars);
t_data		*map_is_valid(t_data *vars);
t_data		*raycasting_base(t_data *vars, int i);
t_data		*init_direction(t_data *vars);
t_data		*side_dist(t_data *vars);
t_data		*colision(t_data *vars);
t_data		*wall_dist(t_data *vars);
t_data		*calcul_text(t_data *vars, int tex_num, int j);
t_data		*take_map_size(int fd, t_data *vars);
t_data		*parse_link(t_data *vars);
t_texture	*load_texture(t_data *vars);
t_data		*take_texture(t_data *vars);
void    	my_mlx_pixel_put(t_data *vars, int x, int y, int color);
int 		destroy(t_data *vars);
int			init_raycasting(t_data *vars);
void    	free_all_data(t_data *vars);
int 		map_is_close(t_data *vars);
t_data  	*take_map(int fd, t_data *vars);
char		*get_next_line(int fd, int fin);
t_data		*map_is_valid(t_data *vars);
t_data		*init_direction(t_data *vars);
int 		transform_color(char *texture);
int 		key_utils(int key, t_data *vars);
int			good_arg(char **argv);
int			move_left(t_data *vars);
int			move_right(t_data *vars);
int			map_is_long(t_data *vars);
int			map_is_close(t_data *vars);
int			rotate_camera_right(t_data *vars);
int			rotate_camera_left(t_data *vars);
void		free_data_if_bad_map(t_data *vars);
void		draw_image(t_data *vars, int i);
void		fill_map(t_data *vars);
#endif
