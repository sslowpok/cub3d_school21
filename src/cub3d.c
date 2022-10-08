/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 13:15:24 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/08 12:21:24 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	init_game(t_game *game)
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
		error_handler("Allocation failed");
		exit (errno);
	}
	return (0);
}

int	make_image(t_game *game)
{
	int	n;

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

int	cub3d(int fd, char *map)
{
	t_game	game;

	init_game(&game);
	if (parse_map(fd, map, &game))
		return (1);
	if (make_image(&game))
		return (error_handler("Cannot load textures"));
	mlx_hook(game.mlx_win, 2, 1L << 0, key_hook, &game);
	mlx_hook(game.mlx_win, 17, 0L, my_if_closed_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	free_map_array(&game);
	free(game.column);
	return (0);
}
