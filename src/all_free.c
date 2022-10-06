//
// Created by Sheryl Slowpoke on 10/6/22.
//

#include "../includes/cub3d.h"

void free_map_array(t_game *game)
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
}