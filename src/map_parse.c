/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:19:43 by sslowpok          #+#    #+#             */
/*   Updated: 2022/09/30 13:42:30 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void check_map_extension(char *map)
{
    char *tmp;

    tmp = ft_strrchr(map, '.');
    if (!tmp || ft_strcmp(tmp, ".cub"))
    {
        error_handler("Error: cannot read the map");
        exit(1);
    }
}

static int check_if_valid(t_game *game)
{
    int	i;

    if (game->floor_color > 16777215 || game->ceil_color > 16777215)
        return (error_handler("Error: floor and ceiling colors are not set."));
    i = -1;
    while (++i < 4)
    {
        if (game->texture[i].ptr == NULL)
            return (error_handler("Error: textures format is invalid."));
    }
    return (0);
}

static unsigned int count_lines(t_game *game, char *map)
{
    unsigned int    res;
    int             fd;
    char            *tmp;

    res = 1;
    fd = open(map, O_RDONLY);
    if (fd < 0)
        return error_handler("Error: cannot open the map");
    tmp = get_next_line(fd);
    while (tmp != NULL)
    {
        res++;
        free(tmp);
        tmp = get_next_line(fd);
        if (res > game->map_temp_h && tmp != (void *)0)
            game->map_height++;
    }
    close(fd);
    return (res);       // lines is 1 more than actual in the map. feature?..
}

int parse_map(int fd, char *map, t_game *game)
{
    char    *line;

    if (parse_textures(game, &line, fd) || check_if_valid(game))
        return (1);
    if (count_lines(game, map) < 3)
        return (1);


    return (0);
}
