/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:38:45 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/15 11:14:40 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count;
	int		n;
	char	*str;

	count = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	str = (char *)malloc(sizeof(char) * count);
	if (!(str))
		return (NULL);
	count = 0;
	n = 0;
	while (s1 && s1[n])
		str[count++] = s1[n++];
	n = 0;
	while (s2 && s2[n])
		str[count++] = s2[n++];
	str[count] = '\0';
	return (str);
}

char	*ft_strjoin2(char const *s1, char const *s2, char c)
{
	int		count;
	int		n;
	char	*str;

	count = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2;
	str = (char *)malloc(sizeof(char) * count);
	if (!(str))
		return (NULL);
	count = 0;
	n = 0;
	while (s1 && s1[n])
		str[count++] = s1[n++];
	str[count++] = c;
	n = 0;
	while (s2 && s2[n])
		str[count++] = s2[n++];
	str[count] = '\0';
	return (str);
}
