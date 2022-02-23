/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 11:45:46 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 11:46:52 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_realloc_cmd(t_token	*cmd, int size)
{
	t_token	*new;
	int		i;

	new = malloc(sizeof(t_token) * (size + 2));
	i = 0;
	while (i < size)
	{
		new[i] = cmd[i];
		i++;
	}
	free(cmd);
	return (new);
}

t_token	*ft_insert_cmd(t_token *cmd, int size, int ins, t_token token)
{
	t_token	*new;
	int		i;
	int		j;

	new = malloc(sizeof(t_token) * (size + 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		if ((i) == ins)
			new[j++] = token;
		else if (i > ins)
			new[j++] = cmd[i - 1];
		else
			new[j++] = cmd[i];
		i++;
	}
	new[j].value = NULL;
	new[j].type = 0;
	free(cmd);
	return (new);
}

t_token	*ft_remove_cmd(t_token *cmd, int size, int del)
{
	t_token	*new;
	int		i;
	int		j;

	new = malloc(sizeof(t_token) * (size + 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != del)
			new[j++] = cmd[i];
		i++;
	}
	new[j].value = NULL;
	new[j].type = 0;
	if (cmd[del].value)
		free(cmd[del].value);
	free(cmd);
	return (new);
}
