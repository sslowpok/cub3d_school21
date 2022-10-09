/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sslowpok <sslowpok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 15:46:46 by sslowpok          #+#    #+#             */
/*   Updated: 2022/10/07 13:28:53 by sslowpok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	ft_count_before_n(char *text)
{
	int	i;

	i = 0;
	while (text[i] && text[i] != '\n')
		i++;
	return (i);
}

static char	*ft_copy_text(int fd, char *text, char *buf)
{
	int		ret;
	int		find_n;
	char	*temp;

	ret = 1;
	find_n = 0;
	while (ret != 0 && find_n == 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (NULL);
		buf[ret] = '\0';
		if (!text)
			text = ft_strdup("");
		if (!text)
			return (NULL);
		temp = text;
		text = ft_strjoin(temp, buf);
		if (!text)
			return (NULL);
		free(temp);
		if (ft_strchr(text, '\n') != 0)
			find_n = 1;
	}
	return (text);
}

static char	*ft_make_line(char	*text)
{
	int		i;
	char	*line;

	i = ft_count_before_n(text);
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, text, i + 2);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*ft_new_line(char *text)
{
	int		i;
	char	*new_text;

	i = ft_count_before_n(text);
	if (text[i] == '\0')
	{
		free(text);
		return (NULL);
	}
	new_text = malloc(sizeof(char) * (ft_strlen(text) - i + 1));
	if (!new_text)
	{
		free(text);
		return (NULL);
	}
	ft_strlcpy(new_text, text + i + 1, ft_strlen(text) - i + 1);
	free(text);
	return (new_text);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*text;

	if ((fd < 0) != 0)
		return (NULL);
	buf = malloc((BUFFER_SIZE + 1) * (sizeof(char)));
	if (!buf)
	{
		free(buf);
		return (NULL);
	}
	text = ft_copy_text(fd, text, buf);
	free(buf);
	if (!text)
		return (NULL);
	line = ft_make_line(text);
	text = ft_new_line(text);
	return (line);
}
