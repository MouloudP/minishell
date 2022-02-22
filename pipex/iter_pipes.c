/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:03:44 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/22 15:43:08 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_all_pid(pid_t *pid, int size)
{
	int	i;
	int	status;

	waitpid(pid[size - 1], &status, 0);
	return (0);
	i = 0;
	status = 1;
	if (!pid)
		return (1);
	while (i < size)
	{
		if (pid && pid[i] && pid[i] > 1)
			waitpid(pid[i], &status, 0);
		++i;
	}
	return (status);
}

int	print_stdout(int fd)
{
	if (fd > 2)
		close(fd);
	if (dup2(1, fd) == -1)
		return (-3);
	return (0);
}

/* must copy the arg list, just modify the tab.
then we can modify and free the first element, then free the tab*/

char	**get_args(t_pipe *pipe_a, t_m *mini, int *redir)
{
	char		**paths;
	char		**args;

	args = NULL;
	paths = get_paths(mini->env_bis);
	if (!paths)
	{
		input_error("Environement", "cant find PATH", 3);
		*redir = -6;
		return (NULL);
	}
	args = args_cpy(pipe_a->parse_cmd, pipe_a->cmd_count);
	if (!args)
	{
		*redir = -7;
		free_split(paths);
		return (args);
	}
	*redir = parse_cmd(&args[0], paths);
	free_split(paths);
	return (args);
}

int	proceed_pipe(int *input_fd, int *pid, t_ep ep, int last_pipe)
{
	char		**args;
	int			redir;
	int			pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	redir = redirections(*(ep.pipe), input_fd, &pipe_fd[1]);
	if (redir < 0)
		return (redir);
	else if (redir == 0 && last_pipe)
		if (print_stdout(pipe_fd[1]) < 0)
			return (-1);
	args = get_args(ep.pipe, ep.m, &redir);
	if (redir == -6 || redir == INVALID_CMD)
		return (free(args), *pid = -1, 0);
	else if (redir < 0)
		return (free(args[0]), free(args), -2);
	else if (redir == VALID_CMD)
	{
		*pid = run_process_command(*input_fd, args, ep.m, pipe_fd);
		if (*pid == -1)
			return (free(args[0]), free(args), -4);
	}
	return (free(args[0]), free(args), 0);
}

int	iter_pipes(t_pipe *pipes, int pipe_size, t_m *mini)
{
	pid_t		*pids;
	int			i;
	int			input_fd;
	t_ep		ep;

	input_fd = 0;
	i = 0;
	pids = malloc(sizeof(pid_t) * pipe_size * 100);
	if (!pids)
		return (-2);
	while (i < pipe_size)
	{	
		ep.m = mini;
		ep.pipe = &pipes[i];
		if (proceed_pipe(&input_fd, &pids[i], ep, i + 1 == pipe_size) < 0)
			return (free(pids), -1);
		++i;
	}
	mini->exit_status = wait_all_pid(pids, pipe_size);
	free(pids);
	if (input_fd != 0)
		close(input_fd);
	return (1);
}
