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
