/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:52:32 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/27 18:24:45 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_replaceenv(t_m *mini, char *name, char *value)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) == 0)
		{
			if (mini->env[i].value)
				free(mini->env[i].value);
			if (value)
			{
				mini->env[i].value = ft_strdup(value);
				mini->env[i].init = 1;
			}
			else
			{
				mini->env[i].value = NULL;
				mini->env[i].init = 0;
			}
			break ;
		}
		i++;
	}
	update_env(mini);
}

void	ft_setenv1(t_m *mini, int *i, t_env *env, char *value)
{
	if (value)
		env[(*i)].value = ft_strdup(value);
	else
		env[(*i)].value = NULL;
	env[++(*i)].name = NULL;
	env[(*i)].init = 1;
	env[(*i)++].value = NULL;
	free(mini->env);
	mini->env = env;
	mini->env_lenght++;
	update_env(mini);
}

void	ft_setenv(t_m *mini, char *name, char *value, int init)
{
	int		i;
	t_env	*env;

	if (ft_hasenv(mini, name))
	{
		ft_replaceenv(mini, name, value);
		return ;
	}
	env = ft_malloc(sizeof(t_env) * (mini->env_lenght + 1));
	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		env[i].name = mini->env[i].name;
		env[i].value = mini->env[i].value;
		env[i].init = mini->env[i].init;
		i++;
	}
	env[i].name = ft_strdup(name);
	env[i].init = init;
	ft_setenv1(mini, &i, env, value);
}

void	ft_removeenv1(t_m *mini, int *j, t_env *env, int temp)
{
	free(mini->env[temp].name);
	free(mini->env[temp].value);
	env[(*j)].name = NULL;
	env[(*j)].init = 1;
	env[(*j)++].value = NULL;
	free(mini->env);
	mini->env = env;
	mini->env_lenght--;
	update_env(mini);
}

void	ft_removeenv(t_m *mini, char *name)
{
	int		i;
	int		j;
	t_env	*env;
	int		temp;

	if (!ft_hasenv(mini, name))
		return ;
	env = ft_malloc(sizeof(t_env) * (mini->env_lenght));
	i = 0;
	j = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (ft_strcmp(mini->env[i].name, name) != 0)
		{
			env[j].name = mini->env[i].name;
			env[j].value = mini->env[i].value;
			env[j].init = mini->env[i].init;
			j++;
		}
		else
			temp = i;
		i++;
	}
	ft_removeenv1(mini, &j, env, temp);
}
