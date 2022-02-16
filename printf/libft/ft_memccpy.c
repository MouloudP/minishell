/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:22:33 by ahamdoun          #+#    #+#             */
/*   Updated: 2020/11/25 11:13:37 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*cpy_dest;
	unsigned char	*cpy_src;

	i = 0;
	cpy_dest = (unsigned char *)dest;
	cpy_src = (unsigned char *)src;
	while (i < n)
	{
		cpy_dest[i] = cpy_src[i];
		if (cpy_dest[i] == (unsigned char)c)
			return ((void *)&cpy_dest[i + 1]);
		i++;
	}
	return (NULL);
}
