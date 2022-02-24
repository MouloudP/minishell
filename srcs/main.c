/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:20:48 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/24 13:23:41 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	free_exit(t_m *mini)
{
	if (mini->exit_char)
	{
		free(mini->exit_char);
		mini->exit_char = NULL;
	}
}

void	free_all(t_m *mini)
{
	rl_clear_history();
	free_env(mini);
	free_env_bis(mini);
	free_exit(mini);
}

void	minishell(char **line, t_m *mini, t_token *cmd)
{
	add_history(*line);
	if (*line[0])
	{
		if (!ft_check_syntax(*line))
		{
			cmd = ft_partsing(*line, mini);
			free_cmd(cmd);
			free_pipe(mini);
		}
		else
			mini->exit_status = 1;
	}
	if (mini->canceldelimiters == 1)
	{
		dup2(mini->dup_fd, 0);
		mini->canceldelimiters = 0;
		signal(SIGINT, cancel_c);
	}
	free(*line);
	if (mini->end == -1)
		*line = readline("\e[0;35mMini\e[0;33mshell $>\e[0;37m ");
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_m		mini;
	t_token	*cmd;

	(void) argc;
	(void) argv;
	setup_signal(&mini);
	get_env(env, &mini);
	mini.exit_status = 0;
	mini.exit_char = ft_malloc(sizeof(char) * 4);
	line = readline("\e[0;35mMini\e[0;33mshell $>\e[0;37m ");
	cmd = NULL;
	while (line && mini.end == -1)
	{
		minishell(&line, &mini, cmd);
	}
	free_all(&mini);
	return (mini.exit_status);
}
