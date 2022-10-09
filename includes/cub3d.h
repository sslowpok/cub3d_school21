/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:47:54 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/07 13:50:52 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define PI2		6.28318530718

typedef struct s_rgb
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_rgb;

typedef struct s_texture
{
	void			*ptr;
	unsigned int	*data_addr;
	double			aspect_ratio;
	unsigned int	width;
	unsigned int	height;
}	t_texture;

typedef struct s_dtype
{
	double	x;
	double	y;
}	t_dtype;

typedef struct s_column
{
	double			distance;
	unsigned int	height;
	double			texture_pos;
	char			dir;
}				t_column;

typedef struct s_game
{
	void			*mlx;
	void			*mlx_win;
	unsigned int	ceil_color;
	unsigned int	floor_color;
	unsigned int	map_temp_h;
	unsigned int	map_height;
	unsigned int	map_length;
	t_rgb			rgb;
	t_texture		texture[4];
	t_column		*column;
	double			p_pos_x;
	double			p_pos_y;
	double			p_angle;
	double			p_vector_x;
	double			p_vector_y;
	float			col_center;
	double			col_scale;
	void			*img_ptr;
	unsigned int	*img_data_addr;
	unsigned int	img_resolution_x;
	unsigned int	img_resolution_y;
	char			**map_array;
}	t_game;

char		*get_next_line(int fd);

int			error_handler(char *msg);
void		check_map_extension(char *map);
int			cub3d(int fd, char *map);
int			parse_map(int fd, char *map, t_game *game);
int			parse_textures(t_game *game, char **line, int fd);
void		raycasting(t_game *game);
void		draw_ceil_floor(t_game *game);
void		draw_walls(t_game *game);
int			validate_map(t_game *game);
int			parse1(t_game *game, char *line);
void		handle_step(int keycode, t_game *game);
int	        key_hook(int keycode, t_game *game);
int	        my_if_closed_window(int keycode, t_game *game);
int			game_loop(t_game *game);

#endif