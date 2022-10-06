/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:15:24 by sslowpok          #+#    #+#             */
/*   Updated: 2022/09/30 13:53:13 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int init_game(t_game *game)
{
    int	i;

    game->ceil_color = 16777216;
    game->floor_color = 16777216;
    game->map_height = 0;
    game->map_temp_h = 0;
    game->img_resolution_x = 1200;
    game->img_resolution_y = 600;
    i = -1;
    while (++i < 5)
        game->texture[i].ptr = NULL;
    game->mlx = mlx_init();
    game->column = malloc(sizeof(t_column) * game->img_resolution_x);
    if ((game->mlx == NULL) || !game->column)
    {
        ft_putstr_fd("Error: Cannot allocation failed", 2);
        exit (errno);
    }
    return 0;
}

void handle_step(int keycode, t_game *game)
{
    if (keycode == 13)
    {
        game->p_pos_x += 0.1 * game->p_vector_x;
        game->p_pos_y += 0.1 * game->p_vector_y;
    }
    else if (keycode == 0)
    {
        game->p_pos_x += 0.1 * game->p_vector_y;
        game->p_pos_y -= 0.1 * game->p_vector_x;
    }
    else if (keycode == 2)
    {
        game->p_pos_x -= 0.1 * game->p_vector_y;
        game->p_pos_y += 0.1 * game->p_vector_x;
    }
    else if (keycode == 1)
    {
        game->p_pos_x -= 0.1 * game->p_vector_x;
        game->p_pos_y -= 0.1 * game->p_vector_y;
    }
}

static int key_hook(int keycode, t_game *game)
{
    if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2)
        handle_step(keycode, game);
    if (keycode == 123)
        game->p_angle -= 0.1;
    if (keycode == 124)
        game->p_angle += 0.1;
    if (keycode == 53)
        exit(0);
    __sincos(game->p_angle, &game->p_vector_y, &game->p_vector_x);
    return 0;
}

static int	my_if_closed_window(int keycode, t_game *game)
{
    (void) keycode;
    (void) game;
    exit(0);
}

void draw_ceil_floor(t_game *game)
{
    unsigned int    i;

    i = -1;
    while (++i < game->img_resolution_x * game->img_resolution_y / 2)
        game->img_data_addr[i] = game->ceil_color;
    while (i++ < game->img_resolution_x * game->img_resolution_y)
        game->img_data_addr[i - 1] = game->floor_color;
}

static double	put_addr(t_game *game, unsigned int x, int *max_height, int *y)
{
    int	src_y;

    if (game->column[x].height > game->img_resolution_y)
    {
        src_y = (game->column[x].height - game->img_resolution_y) / 2;
        *y = -1;
        *max_height = game->img_resolution_y;
    }
    else
    {
        src_y = 0;
        *y = -1 + (game->img_resolution_y - game->column[x].height) / 2;
        *max_height = *y + game->column[x].height;
    }
    return (src_y);
}

static void	draw_wall_scaled(t_game *game, unsigned int t_id, \
unsigned int x)
{
    const double		step = (double)game->texture[t_id].height / \
	game->column[x].height;
    const unsigned int	src_x = game->column[x].texture_pos * \
	game->texture[t_id].width;
    double				src_y;
    int					y;
    int					max_height;

    src_y = step * put_addr(game, x, &max_height, &y);
    while (++y < max_height)
    {
        game->img_data_addr[y * game->img_resolution_x + x] = \
				game->texture[t_id].data_addr[(unsigned)src_y * \
				game->texture[t_id].width + src_x];
        src_y += step;
    }
}

void draw_walls(t_game *game)
{
    unsigned int	ray;
    unsigned int	texture_id;

    ray = -1;
    while (++ray < game->img_resolution_x)
    {
        texture_id = ft_strchr("NSWE", game->column[ray].dir) - "NSWE";
        draw_wall_scaled(game, texture_id, ray);
    }
}

int	game_loop(t_game *game)
{
    raycasting(game);
    draw_ceil_floor(game);
    draw_walls(game);

    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img_ptr, 0, 0);
    return (0);
}

int make_image(t_game *game)
{
    int n;

    game->mlx_win = mlx_new_window(game->mlx, game->img_resolution_x, \
	game->img_resolution_y, "cub3D");
    if (!game->mlx_win)
        return (errno);
    game->img_ptr = mlx_new_image(game->mlx, game->img_resolution_x, \
	game->img_resolution_y);
    if (!game->img_ptr)
        return (errno);
    game->img_data_addr = (unsigned int *)mlx_get_data_addr(game->img_ptr, \
	&n, &n, &n);
        return (0);
}


int cub3d(int fd, char *map)
{
    (void) fd;
    (void) map;

    t_game game;
    init_game(&game);
    parse_map(fd, map, &game);
    if (make_image(&game))
        return (error_handler("Error: cannot load textures"));


    // game play
    mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
    mlx_hook(game.mlx_win, 17, 0L, my_if_closed_window, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);


    // free game
    
    return (0);
}