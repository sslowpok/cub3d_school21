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

static int parse_textures(t_game *game, char **line, int fd)
{
    int     res;
    char    *tmp;

    res = 0;
    tmp = get_next_line(fd);
    *line = ft_strtrim(tmp, " ");
    free(tmp);
    while (*line != NULL)
    {
        if (**line == 'N' || **line == 'S' || **line == 'W' || **line == 'E')
        {
            res = parse_textures1(game, *line);
        }
        else if (**line == 'C' || **line == 'F')
        {
            res = parse_textures2(game, *line, **line);
        }
        else if (**line != '\0' && (**line == '1' || **line == ' '))
            return (0);
        free(*line);
        if (res)
            return (1);
        *line = get_next_line(fd);
        game->map_temp_h++;
    }
    if (!(*line))
        return (error_handler("Error: map does not exist"));

    return (0);
}

int parse_map(int fd, __unused char *map, t_game *game)
{
    char    *line;


    if (parse_textures(game, &line, fd))
        return (1);

    return (0);
}
