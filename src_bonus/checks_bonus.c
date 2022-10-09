/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:12:23 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/09 17:14:49 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	insert_hero_pos(t_game *game, int y, int x)
{
	game->p_pos_x = x + 0.5;
	game->p_pos_y = y + 0.5;
	game->p_angle = M_PI_2 * (double)(ft_strchr("ESWN", game->map_array[y][x]) \
	- "ESWN");
	game->map_array[y][x] = '0';
	__sincos(game->p_angle, &game->p_vector_y, &game->p_vector_x);
	game->col_center = (float)game->img_resolution_x / 2;
	game->col_scale = 1 / (tan(M_PI_2 / (game->img_resolution_x)));
}

static int	check_symbols(t_game *game)
{
	unsigned int	i;
	int				j;
	int				qty_heroes;

	qty_heroes = 0;
	i = -1;
	while (++i < game->map_height)
	{
		j = -1;
		while (game->map_array[i][++j] != '\0')
		{
			if (!ft_strchr(" 01NSWE", game->map_array[i][j]))
				return (error_handler("Invalid map"));
			if (ft_strchr("NSWE", game->map_array[i][j]))
			{
				if (qty_heroes > 0)
					return (error_handler("Duplicated start position"));
				qty_heroes = 1;
				insert_hero_pos(game, (int) i, (int) j);
			}
		}
	}
	return (0);
}

static int	check_borders(t_game *game)
{
	unsigned int	i;
	unsigned int	k;

	i = -1;
	while (++i < game->map_height)
	{
		k = 0;
		while (game->map_array[i][k])
		{
			if (ft_strchr("0NSWE", game->map_array[i][k]))
			{
				if ((i == 0) || (i == game->map_height - 1) || \
				(k == 0) || (k == ft_strlen(game->map_array[i]) - 1))
					return (error_handler("Map is not closed with walls"));
				if ((game->map_array[i - 1][k] == ' ') || \
				(game->map_array[i + 1][k] == ' ') || \
				(game->map_array[i][k - 1] \
				== ' ') || (game->map_array[i][k + 1] == ' '))
					return (error_handler("Map is not closed with walls"));
			}
			k++;
		}
	}
	return (0);
}

int	validate_map(t_game *game)
{
	unsigned int	i;
	unsigned int	k;

	game->map_length = ft_strlen(game->map_array[0]);
	i = -1;
	while (++i < game->map_height)
	{
		if (game->map_length < (unsigned int)ft_strlen(game->map_array[i]))
			game->map_length = (unsigned int)ft_strlen(game->map_array[i]);
	}
	if (check_symbols(game) || check_borders(game))
		exit(1);
	i = -1;
	while (++i < game->map_height)
	{
		k = game->map_length;
		game->map_array[i][k] = '\0';
		while (game->map_array[i][--k] != '1')
			game->map_array[i][k] = ' ';
	}
	return (0);
}
