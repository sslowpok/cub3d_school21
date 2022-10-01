/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:07:46 by sslowpok          #+#    #+#             */
/*   Updated: 2022/09/30 13:43:20 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    int fd;
    int error_code;
    
    if (argc != 2)
        return (error_handler("Usage: ./cub3d MAP.cub"));
    check_map_extension(argv[1]);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (error_handler("Error: cannot read file"));
        
    // empty file?
    
    error_code = cub3d(fd, argv[1]);
    close(fd);
    
    return (error_code);
}