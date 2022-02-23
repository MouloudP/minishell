/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:13:26 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 12:04:11 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_command(int entry_pipe, int	*pipe_fd, char **parsed_cmd, t_m *mini)
{
	if (dup2(entry_pipe, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		return (-1);
	close_pipe(pipe_fd);
	if (entry_pipe != 0)
		close(entry_pipe);
	if (!parsed_cmd)
		perror("split error");
	if (is_builtin(parsed_cmd[0]))
	{
		run_builtin(parsed_cmd, mini, 0, 1);
		exit(0);
	}
	if (execve(parsed_cmd[0], &parsed_cmd[0], mini->env_bis) == -1)
		input_error("Command execution", parsed_cmd[0], 0);
	return (-1);
}

int	run_process_command(int first_pipe, char **pipe_cmd,
t_m *mini, int *new_pipe_fd)
{
	pid_t	pid;

	if (fork_store(&pid) == -1)
		return (-1);
	if (pid == 0)
		return (run_command(first_pipe, new_pipe_fd, pipe_cmd, mini));
	if (dup2(new_pipe_fd[0], first_pipe) == -1)
		return (-1);
	close_pipe(new_pipe_fd);
	return (pid);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}
