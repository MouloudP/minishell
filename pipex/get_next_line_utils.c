/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 10:57:17 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/18 17:38:10 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_n(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*free_null(char *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

int	ft_isline(char *str)
{
	unsigned int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_realloc_cat(char *src, char *dst)
{
	char			*tmp;
	unsigned int	i;

	tmp = malloc(sizeof(char) * (ft_strlen_gnl(src) + ft_strlen_gnl(dst) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	if (dst)
	{
		while (dst[i])
		{
			tmp[i] = dst[i];
			i++;
		}
	}
	while (*src)
	{
		tmp[i] = *src;
		i++;
		src++;
	}
	dst = free_null(dst);
	tmp[i] = '\0';
	return (tmp);
}
