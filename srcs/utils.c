/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:45:45 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/22 12:43:55 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_add_assign(char *str, char *news)
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

void	free_env_bis(t_m *mini)
{
	int	i;

	i = 0;
	while (mini->env_bis[i])
	{
		free(mini->env_bis[i]);
		i++;
	}
	free(mini->env_bis);
}

void	free_pipe(t_m *mini)
{
	int i;

	i = 0;
	while (i < mini->pipe_lenght)
	{
		free(mini->pipe[i].cmd);
		free(mini->pipe[i].infile);
		free(mini->pipe[i].outfile);
		free(mini->pipe[i].parse_cmd);
		i++;
	}
	free(mini->pipe);
}

void	ft_exit_error(char *str, int num)
{
	write(2, str, ft_strlen(str));
	exit(num);
}