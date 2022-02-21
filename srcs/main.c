/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:20:48 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/21 13:02:57 by pleveque         ###   ########.fr       */
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
	mini.exit_status = 0;
	line = readline("\e[0;35mLeShell\e[0;33mDeLaHonte $>\e[0;37m ");
	while (line && mini.end == -1)
	{
		add_history(line);
		if (line[0])
		{
			cmd = ft_partsing(line, &mini);
			cmd->mini = mini;
			// if (cmd_built(cmd, &mini) == 0)
			// {
			// 	//get_absolute_path(cmd);
			// 	//if (!cmd[0])
			// 	//	ft_printf("Command not found !\n");
			// 	//else
			// 	//	exec_cmd(cmd);
			// }
			free_cmd(cmd);
			free_pipe(&mini);
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