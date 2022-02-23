/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:26:05 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 19:42:18 by ahamdoun         ###   ########.fr       */
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
			return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
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
	return (EXIT_SUCCESS);
}

void	get_env(char **env, t_m *mini)
{
	int		i;
	char	*temp;

	i = 0;
	while (env[i])
		i++;
	mini->env = ft_malloc(sizeof(t_env) * (i + 1));
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

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = (unsigned int)(n * -1);
	}
	else
		nbr = (unsigned int)n;
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd((char)(nbr % 10 + '0'), fd);
}

char	*ft_exit_satus(int n, t_m *mini)
{
	int		nb;
	int		i;

	nb = n;
	i = 0;
	while (n >= 10)
	{
		i++;
		n = n / 10;
	}
	i++;
	ft_bzero(mini->exit_char, 4);
	mini->exit_char[i] = '\0';
	n = nb;
	while (n >= 10)
	{
		mini->exit_char[--i] = ((n % 10) + '0');
		n = n / 10;
	}
	mini->exit_char[--i] = ((n % 10) + '0');
	return (mini->exit_char);
}
