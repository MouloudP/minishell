/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 15:57:54 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/22 17:18:03 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_c(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		++i;
	return (i);
}

char	**first_split(char *s, char c)
{
	char	**sep;
	int		size_alpha;
	int		size_omega;

	sep = malloc(sizeof(char *) * 3);
	if (!sep)
		return (NULL);
	size_alpha = ft_strlen_c(s, c);
	size_omega = ft_strlen_c(s, '\0');
	sep[0] = malloc(sizeof(char) * (size_alpha + 1));
	sep[1] = malloc(sizeof(char) * (size_omega + 1));
	sep[2] = NULL;
	if (!sep[0] || !sep[1])
		return (free(sep[0]), free(sep[1]), free(sep), NULL);
	ft_strlcpy(sep[0], s, size_alpha + 1);
	sep[0][size_alpha + 1] = '\0';
	if (s[size_alpha] != c)
		return (free(sep[1]), sep[1] = NULL, sep);
	else
		ft_strlcpy(sep[1], &s[size_alpha + 1], size_omega + 1);
	return (sep);
}
