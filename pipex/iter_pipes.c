/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:03:44 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/19 14:12:56 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	run_process_command(int first_pipe, char **cmd_args, char **env, int *new_pipe_fd)
{
	pid_t	pid;

	if (cmd_args)
	{
		if (fork_store(&pid) == -1)
			return (-1);
		if (pid == 0)
			return (run_command(first_pipe, new_pipe_fd, cmd_args, env));
	}
	if (dup2(new_pipe_fd[0], first_pipe) == -1)
	{
		// free(cmd_args);
		return (-1);
	}
	close_pipe(new_pipe_fd);
	return (pid);
}

int	print_outfiles(int first_pipe, t_str_tab *outfiles)
{
	int	i;

	i = 0;
	while (i < outfiles->size)
	{
		first_pipe = write_command_output(outfiles->str[i], first_pipe);
		++i;
	}
	return (first_pipe);
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

int	iter_pipes(int argc, char **argv, char **env, char **paths)
{
	int			first_pipe;
	int			arg_i;
	t_str_tab	*cmd_args;
	pid_t		*pids;
	int			pipe_fd[2];
	int			i;
	

	(void)argc;
	first_pipe = 0;
	arg_i = 1;
	i = 0;
	pids = malloc(sizeof(pid_t) * 30);
	while (argv[arg_i] != NULL)
	{	
		if (pipe(pipe_fd) == -1)
			return (-1);
		arg_i += get_args(&argv[arg_i], &cmd_args, &first_pipe, &pipe_fd[1]);
		cmd_args->str[0] = parse_cmd(cmd_args->str[0], paths);
		pids[i] = run_process_command(first_pipe, cmd_args->str, env, pipe_fd);
		free(cmd_args->str[0]);
		free(cmd_args->str);
		free(cmd_args);
		++i;
	}
	wait_all_pid(pids, i);
	free(pids);
	close(first_pipe);	
	return (1);
}
/* peut importe l'ordre pour < et > leur comportement est le suivant: > {file}
ces redirection n'ont d'impacte que si elles sont suivit d'une commande*/
/* the < addition themselves 
< before cmd = 1 and only one file,
< after cmd = every other args are now files, only the last 1 is take in
if a < have multiple files, the last become the only on source
if error on <, never run the commad
*/
/* each > write on each files, same for >> */