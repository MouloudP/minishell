/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:32:16 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/20 11:44:38 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strclen(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	return (i);
}

int	ft_biggest(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	free_split_int(char **splitted)
{
	free_split(splitted);
	return (-1);
}

void	close_pipe(int *pipe)
{
	close(pipe[1]);
	close(pipe[0]);
}
