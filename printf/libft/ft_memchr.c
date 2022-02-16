/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 10:04:02 by ahamdoun          #+#    #+#             */
/*   Updated: 2020/12/12 10:51:37 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*cpy_s;

	i = 0;
	cpy_s = (unsigned char *)s;
	while (i < n)
	{
		if (cpy_s[i] == (unsigned char)c)
			return ((void *)cpy_s + i);
		i++;
	}
	return (NULL);
}
