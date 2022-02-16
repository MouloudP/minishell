/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:36:29 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/12 11:09:26 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_freetab(char **tab, size_t n)
{
	size_t		count;

	count = 0;
	while (count < n)
	{
		free(tab[count]);
		count++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_size_str(char const *str, char c)
{
	size_t		size;
	int			finish;

	size = 0;
	finish = 1;
	if (!str)
		return (size);
	while (*str != '\0')
	{
		if (*str != c && finish)
			size++;
		finish = *str == c;
		str++;
	}
	return (size);
}

static char	*ft_create_word(char const *str, size_t n)
{
	size_t		count;
	char		*dest;

	dest = malloc(sizeof(char) * (n + 1));
	if (!(dest))
		return (NULL);
	count = 0;
	while (count < n)
	{
		dest[count] = str[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

char	**ft_split2(char const *str, char c, size_t n, size_t count)
{
	size_t		i;
	char		**tab;

	tab = malloc(sizeof(char *) * (n + 1));
	if (!(tab))
		return (NULL);
	i = 0;
	while (i < n && str)
	{
		count = 0;
		while (*str && *str == c)
			str++;
		while (*str && *str != c)
		{
			count++;
			str++;
		}
		tab[i] = ft_create_word((str - count), count);
		if (!(tab[i]))
			return (ft_freetab(tab, i));
		i++;
	}
	tab[n] = NULL;
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	size_t		n;
	size_t		count;

	n = ft_size_str(str, c);
	count = 0;
	return (ft_split2(str, c, n, count));
}
