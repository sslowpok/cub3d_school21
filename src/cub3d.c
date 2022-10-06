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
    int i;

    game->mlx = mlx_init();
    if (!game->mlx)
    {
        error_handler("Error: allocation failed");
        exit(1);
    }
    game->floor_color = 16777216;
    game->ceil_color =  16777216;
    game->map_height = 0;
//    game->width
    game->map_temp_h = 0;
    game->img_resolution_x = 1200;
    game->img_resolution_y = 600;


    i = -1;
    while (++i < 5)
        game->texture[i].ptr = NULL;
    return 0;
}

/*
 * static void	init_game(t_game *game)
{
	int	i;

	game->ceil_color = 16777216;
	game->ceil_color_old = 8778996;
	game->floor_color = 16777216;
	game->floor_color_old = 9578022;
	game->map_hght = 0;
	game->map_h_tmp = 0;
	game->img_resolution_x = 2400;
	game->img_resolution_y = 1200;
	i = -1;
	while (++i < 5)
		game->textur[i].ptr = NULL;
}

static void	init_alloc_game(t_game *game)
{
	game->mlx = mlx_init();
	game->column = malloc(sizeof(t_column) * game->img_resolution_x);
	if ((game->mlx == NULL) || !game->column)
	{
		ft_putstr_fd("Error\nCannot allocate mamory\n", 2);
		exit (errno);
	}
}
 */


static int key_hook(int keycode, __unused t_game *game)
{
    if (keycode == 53) // esc
        exit(0);
//    __sincos(game->p_angle, &game->p_vect_y, &game->p_vect_x);
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

int	game_loop(t_game *game)
{
//    my_raycasting(game);
//    draw_walls(game);
    draw_ceil_floor(game);

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