/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:26:05 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/22 18:29:19 by pleveque         ###   ########.fr       */
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

void	ft_setenv(t_m *mini, char *name, char *value, int init)
{
	int		i;
	t_env	*env;

	if (ft_hasenv(mini, name))
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
		env[i].init = mini->env[i].init;
		i++;
	}
	env[i].name = ft_strdup(name);
	env[i].init = init;
	if (value)
		env[i].value = ft_strdup(value);
	else
		env[i].value = NULL;
	env[++i].name = NULL;
	env[i].init = 1;
	env[i++].value = NULL;
	free(mini->env);
	mini->env = env;
	mini->env_lenght++;
	update_env(mini);
}

void	ft_removeenv(t_m *mini, char *name)
{
	int		i;
	int		j;
	t_env	*env;

	if (!ft_hasenv(mini, name))
		return ;
	env = malloc(sizeof(t_env) * (mini->env_lenght));
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
		i++;
	}
	env[j].name = NULL;
	env[j].init = 1;
	env[j++].value = NULL;
	free(mini->env);
	mini->env = env;
	mini->env_lenght--;
	update_env(mini);
}
