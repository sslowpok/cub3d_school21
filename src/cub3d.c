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
    int n;
    int i;

    game->mlx = mlx_init();
    if (!game->mlx)
    {
        error_handler("Error: allocation failed");
        exit(1);
    }
    game->floor_color = 16777216;
    game->ceil_color =  16777216;

//    game->height
//    game->width

    game->map_temp_h = 0;
    game->img_resolution_x = 1200;
    game->img_resolution_y = 600;

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
        exit (0);
    return 0;
}

static int	my_if_closed_window(int keycode, t_game *game)
{
    (void) keycode;
    (void) game;
    exit(0);
}

int	game_loop(t_game *game)
{
//    my_raycasting(game);
//    my_store_floor_cell(game);
//    draw_walls(game);
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img_ptr, 0, 0);
    return (0);
}

int cub3d(int fd, char *map)
{
    (void) fd;
    (void) map;
//    int error_code;
    t_game game;
    init_game(&game);

    // parse map

    parse_map(fd, map, &game);




    // game play
    mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
    mlx_hook(game.mlx_win, 17, 0L, my_if_closed_window, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);


    /*
    mlx_hook(data->mlx_win, 2, 0, &key_press, data);
	mlx_hook(data->mlx_win, 3, 0, &key_unpress, data);
	mlx_hook(data->mlx_win, 17, 0, &end_program, data);
	mlx_mouse_hook(data->mlx_win, &ft_mouse, data);
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_loop(data->mlx);
     */

    // free game
    
    return (0);
}