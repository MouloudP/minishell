/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:07:33 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/22 15:43:13 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_split(char **splited)
{
	int	i;

	if (!splited)
		return (NULL);
	i = 0;
	while (splited[i])
	{
		free(splited[i]);
		++i;
	}
	free(splited);
	return (NULL);
}

char	**args_cpy(char **cmd, int size)
{
	char	**res;
	int		i;

	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		res[i] = cmd[i];
		++i;
	}
	res[i] = NULL;
	return (res);
}
