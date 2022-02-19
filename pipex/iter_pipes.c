/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:03:44 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/19 16:14:23 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_process_command(int first_pipe, char **pipe_cmd, char **env, int *new_pipe_fd)
{
	pid_t	pid;

	if (fork_store(&pid) == -1)
		return (-1);
	if (pid == 0)
		return (run_command(first_pipe, new_pipe_fd, pipe_cmd, env));
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
		waitpid(pid[i], 0, 0);
		++i;
	}
	return (0);
}

int	iter_pipes(t_pipes *pipes, char **env, char **paths)
{
	int			first_pipe;
	pid_t		*pids;
	int			pipe_fd[2];
	int			i;
	int			input_fd;
	int			redir;

	input_fd = 0;
	i = 0;
	pids = malloc(sizeof(pid_t) * pipes->size);
	if (!pids)
		return (-2);
	while (i < pipes->size)
	{	
		if (pipe(pipe_fd) == -1)
			return (-1);
		redir = redirections(pipes->pipe[i], &input_fd, &pipe_fd[1]);
		if (redir < 0)
			return (redir);
		if (redir == 0 && i + 1 == pipes->size)
		{
			close(*output_fd);
			if (dup2(1, *output_fd) == -1)
				return (free(pids), -3);
		}
		pipes->pipe[i]->cmd[0] = parse_cmd(pipes->pipe[i]->cmd[0], paths);
		if (!parse_cmd)
			return (free(pids), -2);
		pids[i] = run_process_command(input_fd, pipes->pipe[i]->cmd, env, pipe_fd);
		if (pids[i] < 0)
			return (free(pids), -4);
		free(pipes->pipe[i]->cmd->str[0]);
		++i;
	}
	wait_all_pid(pids, i);
	free(pids);
	close(input_fd);
	return (1);
}
