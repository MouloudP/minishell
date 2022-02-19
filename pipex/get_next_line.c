/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 16:18:07 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/18 17:38:23 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*crop_line(char *src)
{
	char		*dst;
	size_t		len;

	len = ft_strlen_n(src);
	dst = ft_realloc_cat(&src[len], NULL);
	src = free_null(src);
	if (!dst)
		return (NULL);
	return (dst);
}

char	*hydrate_line(char *src)
{
	char		*dst;
	size_t		len;
	size_t		i;

	len = 0;
	while (src[len] != '\0' && src[len] != '\n')
		len++;
	if (src[len] == '\n')
		len++;
	if (len == 0)
		return (NULL);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*read_buff(char *buffer, int fd)
{
	int	readed;

	if (BUFFER_SIZE == 0)
		return (NULL);
	if (buffer)
		buffer = free_null(buffer);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	readed = read(fd, buffer, BUFFER_SIZE);
	if (readed < 0)
	{
		buffer = free_null(buffer);
		return (NULL);
	}
	buffer[readed] = '\0';
	return (buffer);
}

char	*free_all(char **buffer, char **line, char **res)
{
	if (*buffer)
		*buffer = free_null(*buffer);
	if (*line)
		*line = free_null(*line);
	if (*res)
		*res = free_null(*res);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char					*buffer;
	static char				*line = NULL;
	char					*res;

	buffer = NULL;
	res = NULL;
	while (!buffer || (!ft_isline(line)
			&& ft_strlen_gnl(buffer) == BUFFER_SIZE))
	{
		buffer = read_buff(buffer, fd);
		if (!buffer)
			return (free_all(&buffer, &line, &res));
		line = ft_realloc_cat(buffer, line);
		if (!line)
			return (free_all(&buffer, &line, &res));
	}
	res = hydrate_line(line);
	line = crop_line(line);
	if (!line || !res)
		return (free_all(&buffer, &line, &res));
	if (line && ft_strlen_gnl(line) == 0 && line[0] != '\n')
		line = free_null(line);
	buffer = free_null(buffer);
	return (res);
}
