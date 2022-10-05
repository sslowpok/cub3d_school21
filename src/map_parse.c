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

int parse1_continue(__unused t_game *game, char *line, __unused int index)
{
//    int     len;
    char    *tmp;

    printf("PARSE1\n");

    tmp = line;
//    len = ft_strlen(line);
//    if (len < 5)
    printf("%s\n", tmp);


    return (0);
}

int parse1(t_game *game, char *line)
{
    int index;

    if (line[0] == 'N' && line[1] == 'O')
        index = 0;
    else if (line[0] == 'S' && line[1] == 'O')
        index = 1;
    else if (line[0] == 'W' && line[1] == 'E')
        index = 2;
    else if (line[0] == 'E' && line[1] == 'A')
        index = 3;
    else
        return error_handler("Error: wrong texture format. Need \"NO, SO, WE, EA\"");
    if (game->texture[index].ptr != NULL)
        return error_handler("Error: texture is duplicated.");
    if (line[2] != ' ')
        return error_handler("Error: wrong texture format. Need \"NO, SO, WE, EA\" and path");
    line += 2;
    while (*line && *line == ' ')
        line++;
    return (parse1_continue(game, line, index));
}

int parse2(__unused t_game *game, __unused char *line)
{
    return (0);
}

static int parse_textures(__unused t_game *game, char **line, int fd)
{
    int     error_code;
    char    *tmp;

    error_code = 0;
    tmp = get_next_line(fd);
    *line = ft_strtrim(tmp, " ");
    free(tmp);
    while ((*line) != NULL)
    {
        printf("line: %s", *line);

        if (**line == 'N' || **line == 'S' || **line == 'W' || **line == 'E')
            error_code = parse1(game, *line);
        else if (**line == 'C' || **line == 'F')
           error_code = parse2()
        else if (**line != '\0' && (**line == '1' || **line == ' '))
            return (0);

        if (error_code)
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
