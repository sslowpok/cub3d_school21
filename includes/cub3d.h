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

typedef struct s_texture
{
    void			*ptr;
    unsigned int	*data_addr;
    double			aspect_ratio;
    unsigned int	width;
    unsigned int	height;
}	t_texture;

typedef struct s_rgb
{
    unsigned int	r;
    unsigned int	g;
    unsigned int	b;
}	t_rgb;

typedef struct s_game
{
    void    *mlx;
    void    *mlx_win;

    char    **map;

    unsigned int	ceil_color;
    unsigned int	floor_color;

    unsigned int    map_temp_h;

    t_texture texture[4];
    t_rgb			rgb;

    void			*img_ptr;
    unsigned int	*img_data_addr;
    unsigned int	img_resolution_x;
    unsigned int	img_resolution_y;
    
} t_game;

char	*get_next_line(int fd);

int error_handler(char *msg);
void check_map_extension(char *map);
int cub3d(int fd, char *map);
int game_play(t_game *game);
int parse_map(int fd, char *map, t_game *game);
int	parse_textures1(t_game *game, char *line);
int	parse_textures2(t_game *game, char *line, char c);



#endif