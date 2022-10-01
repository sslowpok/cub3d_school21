//
// Created by Sheryl Slowpoke on 10/1/22.
//

#include "../includes/cub3d.h"


static int key_hook(int keycode, __unused t_game *game)
{

//    if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2) // w a s d
//    {
//        // choose_step
//    }
//    if (keycode == 123) // left arrow
//        game->p_angle -= 0.05;
//    if (keycode == 124) // right arrow
//        game->p_angle += 0.05;
//    if (keycode == 8 || keycode == 49) // c v
//    {
//        tmp = game->ceil_color;
//        game->ceil_color = game->ceil_color_old;
//        game->ceil_color_old = tmp;
//        tmp = game->floor_color;
//        game->floor_color = game->floor_color_old;
//        game->floor_color_old = tmp;
//    }
    if (keycode == 53) // esc
        exit (0);
//    __sincos(game->p_angle, &game->p_vect_y, &game->p_vect_x);
    return (0);

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

int game_play(t_game *game)
{
    mlx_hook(game->mlx_win, 2, 1L << 0, key_hook, game);
    mlx_hook(game->mlx_win, 17, 0L, my_if_closed_window, game);
    mlx_loop_hook(game->mlx, game_loop, game);
    mlx_loop(game->mlx);
    return (0);
}
