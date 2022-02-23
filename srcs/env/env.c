/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:26:05 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 11:54:41 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mini_export(char **cmd, t_m *mini, int out_fd)
{
	int		i;
	char	**sep;

	i = 1;
	while (cmd[i])
	{
		sep = first_split(cmd[i], '=');
		if (!sep)
			return (1);
		if (!sep[1])
			ft_setenv(mini, sep[0], NULL, 0);
		else
			ft_setenv(mini, sep[0], sep[1], 1);
		free(sep[0]);
		free(sep[1]);
		free(sep);
		++i;
	}
	if (i == 1)
		ft_printexport(mini, out_fd);
	return (0);
}

int	ft_mini_unset(char **cmd, t_m *mini)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_removeenv(mini, cmd[i]);
		i++;
	}
	return (0);
}

void	get_env(char **env, t_m *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
		i++;
	mini->env = malloc(sizeof(t_env) * (i + 1));
	mini->env_lenght = (i + 1);
	i = -1;
	while (env[++i])
	{
		temp = ft_strchr(env[i], '=');
		mini->env[i].name = ft_strndup(env[i], temp - env[i]);
		mini->env[i].value = ft_strdup(temp + 1);
		mini->env[i].init = 1;
	}
	mini->env[i].name = NULL;
	mini->env[i].value = NULL;
	mini->env[i].init = 0;
	mini->env_bis = env;
	update_env(mini);
}

char	*ft_getenv(t_m *mini, char *name)
{
	int	i;

	i = 0;
	//if (ft_strcmp("?", name))
	//	return (itoa(mini->exit_status, NULL, 10));
	while (i < (mini->env_lenght - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) == 0)
			return (mini->env[i].value);
		i++;
	}
	return (NULL);
}

int	ft_hasenv(t_m *mini, char *name)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) == 0)
			return (1);
		i++;
	}
	return (0);
}
