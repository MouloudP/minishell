/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:45:45 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 19:42:18 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fa(char *str, char *news)
{
	free(str);
	return (news);
}

t_token	free_and_return(char *str, t_token token)
{
	free(str);
	return (token);
}

char	**ft_realloc(char **cmd, int size)
{
	char	**new;
	int		i;

	new = ft_malloc(sizeof(char *) * size + 1);
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

void	free_cmd(t_token *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].value)
		free(cmd[i].value);
	free(cmd);
}

void	free_env(t_m *mini)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		free(mini->env[i].value);
		free(mini->env[i].name);
		i++;
	}
	free(mini->env);
}
