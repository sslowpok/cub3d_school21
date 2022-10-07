/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:15:24 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/07 13:43:11 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_step(int keycode, t_game *game)
{
	if (keycode == 13)
	{
		game->p_pos_x += 0.2 * game->p_vector_x;
		game->p_pos_y += 0.2 * game->p_vector_y;
	}
	else if (keycode == 0)
	{
		game->p_pos_x += 0.2 * game->p_vector_y;
		game->p_pos_y -= 0.2 * game->p_vector_x;
	}
	else if (keycode == 2)
	{
		game->p_pos_x -= 0.2 * game->p_vector_y;
		game->p_pos_y += 0.2 * game->p_vector_x;
	}
	else if (keycode == 1)
	{
		game->p_pos_x -= 0.2 * game->p_vector_x;
		game->p_pos_y -= 0.2 * game->p_vector_y;
	}
}

static int	key_hook(int keycode, t_game *game)
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
	raycasting(game);
	draw_ceil_floor(game);
	draw_walls(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img_ptr, 0, 0);
	return (0);
}
