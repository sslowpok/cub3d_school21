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

void init_game(t_game *game)
{
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        error_handler("Error: allocation failed");
        exit(1);
    }
}

int cub3d(int fd)
{
    t_game *game;
    init_game(game);



    // free game
    
    return (0);
}