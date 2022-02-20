/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:03:44 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/20 16:05:37 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_process_command(int first_pipe, char **pipe_cmd, t_m *mini, int *new_pipe_fd)
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

int	wait_all_pid(pid_t *pid, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pid[i] != -1)
			waitpid(pid[i], 0, 0);
		++i;
	}
	return (0);
}

int	iter_pipes(t_pipe *pipes, int pipe_size, t_m *mini, char **paths)
{
	pid_t		*pids;
	int			pipe_fd[2];
	int			i;
	int			input_fd;
	int			redir;

	input_fd = 0;
	i = 0;
	pids = malloc(sizeof(pid_t) * pipe_size);
	if (!pids)
		return (-2);
	while (i < pipe_size)
	{	
		if (pipe(pipe_fd) == -1)
			return (-1);
		redir = redirections(&pipes[i], &input_fd, &pipe_fd[1]);
		if (redir < 0)
			return (redir);
		if (redir == 0 && i + 1 == pipe_size)
		{
			close(pipe_fd[1]);
			if (dup2(1, pipe_fd[1]) == -1)
		 		return (free(pids), -3);
		}
		redir = parse_cmd(&pipes[i].parse_cmd[0], paths);
		if (redir < 0)
			return (free(pids), -2);
		else if (redir == 1)
		{
			pids[i] = run_process_command(input_fd, pipes[i].parse_cmd, mini, pipe_fd);
			if (pids[i] == -1)
				return (free(pids), -4);
		}
		++i;
	}
	wait_all_pid(pids, i);
	free(pids);
	if (input_fd != 0)
		close(input_fd);
	return (1);
}
