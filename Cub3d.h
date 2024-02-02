/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhennequ <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 14:18:51 by bhennequ          #+#    #+#             */
/*   Updated: 2023/11/23 16:04:33 by bhennequ         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080
# define BUFFER_SIZE 1024

# include <math.h>
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include "minilibx-linux/mlx.h"
# include "minilibx-linux/mlx_int.h"

typedef struct s_point
{
	int		x;
	int		y;
	char	dir;
}				t_point;

typedef struct s_path
{
	char	*path_north;
	char	*path_south;
	char	*path_west;
	char	*path_east;
	char	*sol;
	char	*plafond;
	char	*door;
	int		pn;
	int		ps;
	int		pw;
	int		pe;
	int		so;
	int		pl;
}				t_path;

typedef struct s_position
{
	double	x;
	double	y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	raydirx;
	double	raydiry;
	double	camerax;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	double	perpwalldist;
	int		texy;
	int		texx;
	int		side;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		lineheight;
	int		drawstart;
	int		drawend;
	double	centre_x;
	double	centre_y;
}				t_position;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		line_length;
}				t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_pointer;
	void		*win;
	void		*img;
	void		*addr;
	int			endian;
	int			color;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			img_width;
	int			img_heigth;
	char		**map;
	int			size_line;
	int			size_map;
	int			error;
	int			color_sol;
	int			color_plafond;
	int			door;
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
t_data		*take_map3(t_data *vars);
t_data		*parse_link(t_data *vars);
t_texture	*load_texture(t_data *vars);
t_data		*take_texture(t_data *vars);
void		my_mlx_pixel_put(t_data *vars, int x, int y, int color);
int			destroy(t_data *vars);
int			init_raycasting(t_data *vars);
void		free_all_data(t_data *vars);
int			map_is_close(t_data *vars);
t_data		*take_map(int fd, t_data *vars);
char		*get_next_line(int fd, int fin);
char		*dup_space(char *str);
t_data		*map_is_valid(t_data *vars);
t_data		*init_direction(t_data *vars);
int			transform_color(char *texture, t_data *vars);
int			key_utils(int key, t_data *vars);
int			good_arg(char **argv);
int			move_left(t_data *vars);
int			move_right(t_data *vars);
int			map_is_long(t_data *vars);
int			map_is_close(t_data *vars);
int			rotate_camera_right(t_data *vars);
int			rotate_camera_left(t_data *vars);
int			condition_map_close(int i, int j, t_data *vars);
int			condition_carac_valid(char c, int door);
int			mouse_event(int x, int y, t_data *vars);
int			jsp(t_data *vars);
int			valid_texture_path(t_data *vars);
void		free_data_if_bad_map(t_data *vars);
void		draw_image(t_data *vars, int i);
void		fill_map(t_data *vars);
void		open_door_cond(t_data *vars, int mapx, int mapy);
void		my_mlx_pixel_put2(t_data *vars, int x, int y, unsigned int color);
void		draw_square(t_data *vars);
void		draw_wall(t_data *vars, int i, int j, unsigned int color);
void		draw_character(t_data *vars, int i, int j);
void		draw_minimap(t_data *vars);
void		free_data_if_bad_map2(t_data *vars);
#endif
