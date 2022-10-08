/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:46:31 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/08 12:21:02 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map_array(t_game *game)
{
	unsigned int	height_tmp;

	height_tmp = -1;
	while (++height_tmp < game->map_height)
	{
		if (game->map_array[height_tmp])
			free(game->map_array[height_tmp]);
	}
	if (game->map_array)
		free(game->map_array);
	if (game->column)
		free(game->column);
}
