/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:33:04 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/07 13:35:49 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse1_continue(t_game *game, char *line, int index)
{
	unsigned int	len;
	int				i;
	char			*tmp;

	tmp = line;
	len = ft_strlen(line);
	if (len < 5)
		return (error_handler("Cannot load textures."));
	tmp[len - 1] = '\0';
	if (ft_memcmp(".xpm", tmp + len - 5, 4) == 0)
		game->texture[index].ptr = mlx_xpm_file_to_image(game->mlx, line, \
		(int *)&game->texture[index].width, \
		(int *)&game->texture[index].height);
	else
		return (error_handler("Cannot load textures."));
	if (game->texture[index].ptr == NULL)
		return (error_handler("Cannot load textures."));
	game->texture[index].data_addr = \
		(unsigned int *)mlx_get_data_addr(game->texture[index].ptr, &i, &i, &i);
	game->texture[index].aspect_ratio = game->texture[index].width / \
			game->texture[index].height;
	return (0);
}

int	parse1(t_game *game, char *line)
{
	int	index;

	if (line[0] == 'N' && line[1] == 'O')
		index = 0;
	else if (line[0] == 'S' && line[1] == 'O')
		index = 1;
	else if (line[0] == 'W' && line[1] == 'E')
		index = 2;
	else if (line[0] == 'E' && line[1] == 'A')
		index = 3;
	else
		return (error_handler("Wrong texture format. Need \"NO, SO, WE, EA\""));
	if (game->texture[index].ptr != NULL)
		return (error_handler("Texture is duplicated."));
	if (line[2] != ' ')
		return (error_handler("Wrong texture format." \
		"Need \"NO, SO, WE, EA\" and path"));
	line += 2;
	while (*line && *line == ' ')
		line++;
	return (parse1_continue(game, line, index));
}
