/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:03:44 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 15:36:31 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_all_pid(t_pstat *pipe_status, int size)
{
	int	i;
	int	test;

	i = 0;
	if (!pipe_status)
		return (1);
	while (i < size)
	{
		if (&pipe_status[i] != NULL)
		{
			if (pipe_status[i].pid > 0)
			{
				waitpid(pipe_status[i].pid, &test, 0);
				printf("result: %d\n", test);
			}
			else if (pipe_status[i].pid == -1)
				pipe_status[i].status = 1;
			else if (pipe_status[i].status < 0)
				pipe_status[i].status = 1;
		}
		++i;
	}
	return (1);
}

/* must copy the arg list, just modify the tab.
then we can modify and free the first element, then free the tab*/

char	**get_args(t_pipe *pipe_a, t_m *mini, int *redir, t_pstat *pstat)
{
	char		**paths;
	char		**args;

	args = NULL;
	paths = get_paths(mini->env_bis);
	if (!paths)
	{
		input_error("Environement", "cant find PATH", 3);
		pstat->status = 127;
		*redir = INVALID_CMD;
		return (NULL);
	}
	args = args_cpy(pipe_a->parse_cmd, pipe_a->cmd_count);
	if (!args)
	{
		*redir = INVALID_CMD;
		pstat->status = 127;
		free_split(paths);
		return (NULL);
	}
	*redir = parse_cmd(&args[0], paths);
	if (*redir == INVALID_CMD)
	{
		pstat->status = 127;
		free(args);
	}
	free_split(paths);
	return (args);
}

int	default_pipe(int *input_fd, int *pipe_fd)
{
	int	other_pipe[2];

	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	close(pipe_fd[0]);
	if (pipe(other_pipe) == -1)
		return (-1);
	close(other_pipe[1]);
	*input_fd = other_pipe[0];
	return (0);
}

int	proceed_pipe(int *input_fd, t_pstat *pstat, t_ep *ep, int last_pipe)
{
	char		**args;
	int			redir;
	int			pipe_fd[2];

	if (pipe(pipe_fd) == INVALID_FD)
		return (INVALID_FD);
	redir = redirections(*(ep->pipe), input_fd, &pipe_fd[1]);
	if (redir == 0 && last_pipe && print_stdout(pipe_fd[1]) < 0)
		return (-2);
	else if (redir == INVALID_FD)
		return (pstat->status = 1, default_pipe(input_fd, pipe_fd));
	else if (!ep->pipe->parse_cmd[0])
		return (0);
	args = get_args(ep->pipe, ep->m, &redir, pstat);
	if (redir == INVALID_CMD)
		return (0);
	else if (redir == VALID_CMD)
	{
		pstat->pid = run_process_command(*input_fd, args, ep->m, pipe_fd);
		if (pstat->pid == INVALID_FD)
			return (free(args[0]), free(args),
				input_error("?", "!", 0), pstat->status = 1, -4);
	}
	return (free(args[0]), free(args), 0);
}

int	iter_pipes(t_pipe *pipes, int pipe_size, t_m *mini)
{
	t_pstat		*pipe_status;
	int			i;
	int			input_fd;
	t_ep		ep;

	input_fd = 0;
	pipe_status = malloc(sizeof(t_pstat) * pipe_size);
	if (!pipe_status)
		return (-2);
	i = -1;
	while (++i < pipe_size)
	{
		pipe_status[i].pid = 0;
		pipe_status[i].status = 0;
	}
	i = 0;
	while (i < pipe_size)
	{	
		ep.m = mini;
		ep.pipe = &pipes[i];
		if (proceed_pipe(&input_fd, &pipe_status[i], &ep, i + 1 == pipe_size) < 0)
			return (free(pipe_status), -1);
		++i;
	}
	wait_all_pid(pipe_status, pipe_size);
	mini->exit_status = pipe_status[pipe_size - 1].status;
	if (input_fd > 0)
		close(input_fd);
	printf("exit: %d\n", mini->exit_status);
	return (free(pipe_status), 1);
}
