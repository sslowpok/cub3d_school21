/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:46:55 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/07 13:37:00 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	parse2_1(char **line)
{
	int		i;
	char	tmp[4];

	while (**line == ' ')
		(*line)++;
	i = 0;
	while ((**line) && (**line) != ',' && (**line) != ' ')
	{
		if (ft_isdigit(**line))
			tmp[i] = **line;
		else
			break ;
		(*line)++;
		i++;
	}
	while (**line && **line == ' ')
		(*line)++;
	if (**line != ',' || i > 3)
		return (-1);
	tmp[i] = '\0';
	i = ft_atoi(tmp);
	if (i > 255)
		return (-1);
	(*line)++;
	return (i);
}

int	parse2_2(char **line)
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

void	make_colors(t_game *game, char c)
{
	if (c == 'C')
		game->ceil_color = (game->rgb.r << 16) | (game->rgb.g << 8) | \
		game->rgb.b;
	else
		game->floor_color = (game->rgb.r << 16) | (game->rgb.g << 8) | \
		game->rgb.b;
}

int	parse2(t_game *game, char *line, char c)
{
	int	result;

	if ((c == 'C' && game->ceil_color != 16777216) || \
	(c == 'F' && game->floor_color != 16777216))
		return (error_handler("Floor or ceiling color is duplicated."));
	line++;
	if (*line != ' ')
		return (error_handler("Invalid color format"));
	result = parse2_1(&line);
	if (result < 0)
		return (error_handler("Invalid color format"));
	game->rgb.r = (unsigned) result;
	result = parse2_1(&line);
	if (result < 0)
		return (error_handler("Invalid color format"));
	game->rgb.g = (unsigned) result;
	result = parse2_2(&line);
	if (result < 0)
		return (error_handler("Invalid color format"));
	game->rgb.b = (unsigned) result;
	make_colors(game, c);
	return (0);
}

int	parse_textures(t_game *game, char **line, int fd)
{
	int		error_code;
	char	*tmp;

	error_code = 0;
	tmp = get_next_line(fd);
	*line = ft_strtrim(tmp, " ");
	free(tmp);
	while ((*line) != NULL)
	{
		if (**line == 'N' || **line == 'S' || **line == 'W' || **line == 'E')
			error_code = parse1(game, *line);
		else if (**line == 'C' || **line == 'F')
			error_code = parse2(game, *line, **line);
		else if (**line != '\0' && (**line == '1' || **line == ' '))
			return (0);
		free(*line);
		if (error_code)
			return (1);
		*line = get_next_line(fd);
		game->map_temp_h++;
	}
	if (!(*line))
		return (error_handler("Map does not exist"));
	return (0);
}
