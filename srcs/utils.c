/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:45:45 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/15 15:26:25 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_add_assign(char *str, char *news)
{
	free(str);
	return (news);
}

char	**ft_realloc(char **cmd, int size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * size + 1);
	i = 0;
	while (cmd[i])
	{
		new[i] = cmd[i];
		if (cmd[i])
			free(cmd[i]);
		i++;
	}
	free(cmd);
	new[i] = NULL;
	return (new);
}
