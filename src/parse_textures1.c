//
// Created by Sheryl Slowpoke on 10/1/22.
//

#include "../includes/cub3d.h"

static int	parse_textures1_1(t_game *game, char *line, int sign)
{
    unsigned int	len;
    int				i;
    char			*tmp;

    tmp = line;
    len = ft_strlen(line);
    if (len < 5)
        return (error_handler("Error: cannot load textures"));
    tmp[len - 1] = '\0';
    if (ft_memcmp(".xpm", tmp + len - 5, 4) == 0)
        game->texture[sign].ptr = mlx_xpm_file_to_image(game->mlx, line, \
		(int *)&game->texture[sign].width, (int *)&game->texture[sign].height);
    else
        return (error_handler("Error: cannot load textures"));
    if (game->texture[sign].ptr == NULL)
        return (error_handler("Error: cannot load textures"));
    game->texture[sign].data_addr = \
	(unsigned int *)mlx_get_data_addr(game->texture[sign].ptr, &i, &i, &i);
    game->texture[sign].aspect_ratio = game->texture[sign].width / \
	game->texture[sign].height;
    return (0);
}

int	parse_textures1(t_game *game, char *line)
{
    int	sign;

    if (line[0] == 'N' && line[1] == 'O')
        sign = 0;
    else if (line[0] == 'S' && line[1] == 'O')
        sign = 1;
    else if (line[0] == 'E' && line[1] == 'A')
        sign = 2;
    else if (line[0] == 'W' && line[1] == 'E')
        sign = 3;
    else
        return (error_handler("Error: wrong texture format"));
    if (game->texture[sign].ptr != NULL)
        return (error_handler("Error: texture is duplicated"));
    if (line[2] != ' ')
        return (error_handler("Error: wrong texture format"));
    line += 2;
    while (*line && *line == ' ')
        line++;
    return (parse_textures1_1(game, line, sign));
}