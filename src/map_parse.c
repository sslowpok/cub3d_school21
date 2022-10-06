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
    return (res);       // res is 1 more line than actual in the map. feature?..
}

void insert_hero_pos(t_game *game, int y, int x)
{
    game->p_pos_x = x + 0.5;
    game->p_pos_y = y + 0.5;
    game->p_angle = M_PI_2 * (double) (ft_strchr("ESWN", game->map_array[y][x]) \
	- "ESWN");
    game->map_array[y][x] = '0';
    __sincos(game->p_angle, &game->p_vector_y, &game->p_vector_x);
    game->col_center = (float)game->img_resolution_x / 2;
    game->col_scale = 1 / (tan(M_PI_2 / (game->img_resolution_x)));
}

int check_symbols(t_game *game)
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
                return (error_handler("Error: Invalid map"));
            if (ft_strchr("NSWE", game->map_array[i][j]))
            {
                if (qty_heroes > 0)
                    return (error_handler("Error: Duplicated start position"));
                qty_heroes = 1;
                insert_hero_pos(game, (int) i, (int) j);
            }
        }
    }
    return (0);
}

int check_borders(t_game *game)
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
                {
                    return (error_handler("Error: map is not closed with walls"));
                }
                if ((game->map_array[i - 1][k] == ' ') || \
	(game->map_array[i + 1][k] == ' ') || (game->map_array[i][k - 1] \
 == ' ') || (game->map_array[i][k + 1] == ' '))
                    return (error_handler("Error: map is not closed with walls"));
            }
            k++;
        }
    }
    return (0);
}

int validate_map(t_game *game)
{
    unsigned int    i;
    unsigned int    k;

    game->map_length = ft_strlen(game->map_array[0]);
    i = -1;
    while (++i < game->map_height)
    {
        if (game->map_length < (unsigned int)ft_strlen(game->map_array[i]))
            game->map_length = (unsigned int)ft_strlen(game->map_array[i]);
    }
    if (check_symbols(game) || check_borders(game))
    {
        free_map_array(game);
        return (1);
    }
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

int parse_map(int fd, char *map, t_game *game)
{
    char             *line;
    unsigned int     i;

    if (parse_textures(game, &line, fd) || check_if_valid(game))
        return (1);
    if (count_lines(game, map) < 3)
        return (1);
    game->map_array = malloc(sizeof (char *) * game->map_height);
    if (!game->map_array)
        return error_handler("Error: allocation failed");
    i = -1;
    while (++i < game->map_height)
    {
        game->map_array[i] = malloc(1000);
        if (!game->map_array[i])
            return error_handler("Error: allocation failed");
        ft_memcpy(game->map_array[i], line, ft_strlen(line));
        game->map_array[i][ft_strlen(line) - 1] = '\0';
        free(line);
        line = get_next_line(fd);
    }
    return (validate_map(game));
}
