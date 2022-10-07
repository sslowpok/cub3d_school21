/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 12:35:49 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/07 13:40:18 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_ceil_floor(t_game *game)
{
	unsigned int	i;

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

void	draw_walls(t_game *game)
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
