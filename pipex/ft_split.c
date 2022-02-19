/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 16:47:05 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/18 14:08:16 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static unsigned int	countwords(char const *s, char c)
{
	unsigned int	nbrwords;
	int				i;
	int				inword;

	nbrwords = 0;
	inword = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c && !inword)
		{
			nbrwords++;
			inword = 1;
		}
		else if (s[i] == c)
			inword = 0;
		i++;
	}
	return (nbrwords);
}

static char	*storeword(char *dst, char const *s, char c)
{
	unsigned int	len;
	unsigned int	i;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static void	freewords(char **arr, unsigned int len)
{
	unsigned int	i;

	if (len < 1)
		return ;
	i = 0;
	while (i < len)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**storewords(char **arr, char const *s, char c)
{
	unsigned int	i;
	unsigned int	actualword;
	int				inword;

	i = 0;
	inword = 0;
	actualword = 0;
	while (s[i])
	{
		if (s[i] != c && !inword)
		{
			arr[actualword] = storeword(arr[actualword], &s[i], c);
			if (!arr[actualword])
			{
				freewords(arr, actualword - 1);
				return (NULL);
			}
			actualword++;
			inword = 1;
		}
		else if (s[i] == c)
			inword = 0;
		i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	unsigned int	arrlen;

	if (!s)
		return (NULL);
	arrlen = countwords(s, c);
	arr = malloc(sizeof(char *) * (arrlen + 1));
	if (!arr)
		return (NULL);
	arr[arrlen] = NULL;
	return (storewords(arr, s, c));
}
