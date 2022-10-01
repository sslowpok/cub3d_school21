//
// Created by Sheryl Slowpoke on 10/1/22.
//

#include "../includes/cub3d.h"

static int	pars_textures2_1(char **line)
{
    int		i;
    char	str[4];

    while (**line == ' ')
        (*line)++;
    i = 0;
    while ((**line) && (**line) != ',' && (**line) != ' ')
    {
        if (ft_isdigit(**line))
            str[i] = **line;
        else
            break ;
        (*line)++;
        i++;
    }
    while (**line && **line == ' ')
        (*line)++;
    if (**line != ',' || i > 3)
        return (-1);
    str[i] = '\0';
    i = ft_atoi(str);
    if (i > 255)
        return (-1);
    (*line)++;
    return (i);
}

static int	pars_textures2_2(char **line)
{
    int		i;
    char	str[4];

    while (**line == ' ')
        (*line)++;
    i = 0;
    while ((**line) && (**line) != ' ')
    {
        if (ft_isdigit(**line))
            str[i] = **line;
        else
            break ;
        (*line)++;
        i++;
    }
    while (**line == ' ')
        (*line)++;
    if (**line != '\0' && **line != 10)
        return (-1);
    str[i] = '\0';
    i = ft_atoi(str);
    if (i > 255)
        return (-1);
    (*line)++;
    return (i);
}

static void	pars_textures2_3(t_game *game, char c)
{
    if (c == 'C')
        game->ceil_color = (game->rgb.r << 16) | (game->rgb.g << 8) | \
		game->rgb.b;
    else
        game->floor_color = (game->rgb.r << 16) | (game->rgb.g << 8) | \
		game->rgb.b;
}

int	parse_textures2(t_game *game, char *line, char c)
{
    int			res;

    if ((c == 'C' && game->ceil_color != 16777216) || \
	(c == 'F' && game->floor_color != 16777216))
        return (error_handler("Error: floor / ceiling color duplicated"));
    line++;
    if (*line != ' ')
        return (error_handler("Error: wrong floor / ceiling color format"));
    res = pars_textures2_1(&line);
    if (res < 0)
        return (error_handler("Error: wrong floor / ceiling color format"));
    game->rgb.r = (unsigned)res;
    res = pars_textures2_1(&line);
    if (res < 0)
        return (error_handler("Error: wrong floor / ceiling color format"));
    game->rgb.g = (unsigned)res;
    res = pars_textures2_2(&line);
    if (res < 0)
        return (error_handler("Error: wrong floor / ceiling color format"));
    game->rgb.b = (unsigned)res;
    pars_textures2_3(game, c);
    return (0);
}