/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:30:17 by ahamdoun          #+#    #+#             */
/*   Updated: 2020/12/12 10:55:23 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*copy;
	unsigned int	i;

	copy = ft_strdup(s);
	i = 0;
	if (!copy || !s || !f)
		return (NULL);
	while (copy[i])
	{
		copy[i] = f(i, copy[i]);
		i++;
	}
	return (copy);
}
