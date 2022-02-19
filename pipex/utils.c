/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 14:07:33 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/19 18:09:37 by pleveque         ###   ########.fr       */
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
