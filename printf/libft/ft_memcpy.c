/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:03:25 by ahamdoun          #+#    #+#             */
/*   Updated: 2020/12/16 11:11:46 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (src == NULL && dest == NULL)
		return (NULL);
	str1 = (unsigned char *)src;
	str2 = (unsigned char *)dest;
	while (n > 0)
	{
		*str2++ = *str1++;
		n--;
	}
	return (dest);
}
