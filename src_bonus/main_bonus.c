/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:07:46 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/08 12:21:37 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	int	fd;
	int	error_code;

	if (argc != 2)
		return (error_handler("Usage: ./cub3d MAP.cub"));
	check_map_extension(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error_handler("Cannot read file"));
	error_code = cub3d(fd, argv[1]);
	close(fd);
	return (error_code);
}
