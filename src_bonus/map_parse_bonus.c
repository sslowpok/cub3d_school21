/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:19:43 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/07 13:38:48 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	check_map_extension(char *map)
{
	char	*tmp;

	tmp = ft_strrchr(map, '.');
	if (!tmp || ft_strcmp(tmp, ".cub"))
	{
		error_handler("Cannot read the map");
		exit(1);
	}
}

static int	check_if_valid(t_game *game)
{
	int	i;

	if (game->floor_color > 16777215 || game->ceil_color > 16777215)
		return (error_handler("Floor and ceiling colors are not set."));
	i = -1;
	while (++i < 4)
	{
		if (game->texture[i].ptr == NULL)
			return (error_handler("Textures format is invalid."));
	}
	return (0);
}

static unsigned int	count_lines(t_game *game, char *map)
{
	unsigned int	res;
	int				fd;
	char			*tmp;

	res = 1;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (error_handler("Cannot open the map"));
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
	return (res);
}

int	parse_map(int fd, char *map, t_game *game)
{
	char			*line;
	unsigned int	i;

	if (parse_textures(game, &line, fd) || check_if_valid(game))
		return (1);
	if (count_lines(game, map) < 3)
		return (1);
	game->map_array = malloc(sizeof(char *) * game->map_height);
	if (!game->map_array)
		return (error_handler("Allocation failed"));
	i = -1;
	while (++i < game->map_height)
	{
		game->map_array[i] = malloc(1000);
		if (!game->map_array[i])
			return (error_handler("Allocation failed"));
		ft_memcpy(game->map_array[i], line, ft_strlen(line));
		game->map_array[i][ft_strlen(line) - 1] = '\0';
		free(line);
		line = get_next_line(fd);
	}
	return (validate_map(game));
}
