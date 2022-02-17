/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:26:05 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/17 16:03:28 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

char	*ft_getenv(t_m *mini, char *var)
{
	int i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (ft_strncmp(mini->env[i].name, var, ft_strlen(var)) == 0)
			return (mini->env[i].value);
		i++;
	}
	return (NULL);
}

void	ft_replaceenv(t_m *mini, char *name, char *value)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) == 0)
		{
			free(mini->env[i].value);
			mini->env[i].value = ft_strdup(value);
			break ;
		}
		i++;
	}
}

void	ft_setenv(t_m *mini, char *name, char *value)
{
	int		i;
	t_env	*env;

	if (ft_getenv(mini, name))
	{
		ft_replaceenv(mini, name, value);
		return ;
	}
	env = malloc(sizeof(t_env) * (mini->env_lenght + 1));
	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		env[i].name = mini->env[i].name;
		env[i].value = mini->env[i].value;
		i++;
	}
	env[i].name = ft_strdup(name);
	env[i++].value = ft_strdup(value);
	env[i].name = NULL;
	env[i++].value = NULL;
	free(mini->env);
	mini->env = env;
	mini->env_lenght++;
}

void	ft_printenv(t_m *mini)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (mini->env[i].init)
			ft_printf("%s=%s\n", mini->env[i].name, mini->env[i].value);
		i++;
	}
}