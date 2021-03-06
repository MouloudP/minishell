/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:53:12 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 19:42:18 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(t_m *mini)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	while (mini->env[i].name)
	{
		if (mini->env[i].init)
		{
			temp = ft_strjoin(mini->env[i].name, "=");
			mini->env_bis[j++] = ft_strjoin(temp, mini->env[i].value);
			free(temp);
		}
		i++;
	}
	mini->env_bis[j++] = NULL;
}

void	update_env(t_m *mini)
{
	static int	first = 1;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (mini->env[i].name)
	{
		if (mini->env[i].init)
			j++;
		i++;
	}
	if (first == 0)
		free_env_bis(mini);
	first = 0;
	mini->env_bis = ft_malloc(sizeof(char *) * (j + 1));
	copy_env(mini);
}

void	ft_printenv(t_m *mini, int fd_out)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (mini->env[i].init)
		{
			write(fd_out, mini->env[i].name, ft_strlen(mini->env[i].name));
			write(fd_out, "=", 1);
			write(fd_out, mini->env[i].value, ft_strlen(mini->env[i].value));
			write(fd_out, "\n", 1);
		}
		i++;
	}
}

char	*ft_getenv(t_m *mini, char *name)
{
	int	i;

	i = 0;
	if (ft_strcmp("?", name) == 0)
		return (ft_exit_satus(mini->exit_status, mini));
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
