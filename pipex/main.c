/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:24:13 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/21 16:42:27 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **env)
{
	int		i;
	char	**paths;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
		{
			paths = ft_split(env[i] + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
	}
	return (NULL);
}

/* work like old good regular pipex, return 0 if
everything goes well or 1 if fail*/
int	run_builtin(char **cmd, t_m *mini, int fd_in, int fd_out)
{
	(void) fd_in;
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (ft_mini_pwd(cmd, fd_out));
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (ft_mini_cd(cmd, mini));
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (ft_mini_echo(cmd, fd_out));
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (ft_mini_export(cmd, mini, fd_out));
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (ft_mini_env(mini, fd_out));
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (ft_exit(mini));
	return (0);
}

int	pipex(t_pipe *pipes, int pipe_size, char **env, t_m *mini)
{
	char	**paths;
	pid_t	pid;

	if (pipe_size == 1 && is_builtin(pipes[0].parse_cmd[0]))
	{
		mini->exit_status = run_builtin(pipes[0].parse_cmd, mini, 0, 1);
		return (0);
	}
	if (fork_store(&pid) == -1)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, mini->signal_save);
		mini->end = 1;
		paths = get_paths(env);
		if (!paths)
			return (input_error("Environement", NULL, 4));	
		if (iter_pipes(pipes, pipe_size, mini, paths) == -1)
		{
			free_split(paths);
			return (input_error("Excve", NULL, 0));
		}
		mini->end = 0;
		free_split(paths);
		close(0);
		return (1);
	}
	else
	{
		signal(SIGINT, mini->cancel_c2);
		waitpid(pid, 0, 0);
		signal(SIGINT, mini->cancel_c);
	}
	return (0);
}
