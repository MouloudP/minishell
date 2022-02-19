/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:26:05 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/19 16:47:47 by pleveque         ###   ########.fr       */
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
	mini->env_bis = env;
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

void	ft_setenv(t_m *mini, char *name, char *value, int init)
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

t_env	*ft_copy_env(t_m *mini)
{
	t_env	*new;
	int		i;

	new = malloc(sizeof(t_env) * (mini->env_lenght));
	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		new[i].name = mini->env[i].name;
		new[i].value = mini->env[i].value;
		new[i].init = mini->env[i].init;
		i++;
	}
	return (new);
}

void	ft_copy_part(t_env *srcs, t_env *dest)
{
	srcs->name = dest->name;
	srcs->value = dest->value;
	srcs->init = dest->init;
}

void	ft_printexport(t_m *mini)
{
	int		i;
	int		j;
	t_env	*new;
	t_env	temp;

	i = 0;
	new = ft_copy_env(mini);
	while (i < (mini->env_lenght - 1))
	{
		j = 0;
		while (j < (mini->env_lenght - 1))
		{
			if(new[j + 1].name && ft_strcmp(new[j].name, new[j + 1].name) > 0)
			{
				//swap array[j] and array[j+1]
				ft_copy_part(&temp, &new[j]);
				ft_copy_part(&new[j], &new[j + 1]);
				ft_copy_part(&new[j + 1], &temp);
			}
			j++;
    	}
		i++;
 	}
	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (new[i].init)
			ft_printf("%s=%s\n", new[i].name, new[i].value);
		else
			ft_printf("%s=''\n", new[i].name);
		i++;
	}
	free(new);
}