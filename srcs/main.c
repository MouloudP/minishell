/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:20:48 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 10:00:46 by ahamdoun         ###   ########.fr       */
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

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_m		mini;
	t_token	*cmd;

	(void) argc;
	(void) argv;
	setup_signal(&mini);
	get_env(env, &mini);
	mini.exit_status = 255;
	line = readline("\e[0;35mLeShell\e[0;33mDeLaHonte $>\e[0;37m ");
	while (line && mini.end == -1)
	{
		add_history(line);
		if (line[0])
		{
			if (!ft_check_syntax(line))
			{		
				cmd = ft_partsing(line, &mini);
				cmd->mini = mini;
				free_cmd(cmd);
				free_pipe(&mini);
			}
		}
		if (mini.canceldelimiters == 1)
		{
			dup2(mini.dup_fd, 0);
			mini.canceldelimiters = 0;
			signal(SIGINT, cancel_c);
		}
		free(line);
		if (mini.end == -1)
			line = readline("\e[0;35mLeShell\e[0;33mDeLaHonte $>\e[0;37m ");
	}
	rl_clear_history();
	free_env(&mini);
	free_env_bis(&mini);
	return (mini.end);
}