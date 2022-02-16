/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:56:29 by ahamdoun          #+#    #+#             */
/*   Updated: 2021/09/15 11:45:25 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*s2 == '\0' || s2 == NULL)
		return ((char *)s1);
	while (s1[i] && i < n)
	{
		j = 0;
		while (s2[j] == s1[i + j] && i + j < n)
		{
			if (s2[j + 1] == '\0')
				return ((char *)(s1 + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
