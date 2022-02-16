/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:03:44 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/16 18:09:07 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_first_pipe(char **argv, char **env, char **paths)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (limited_stdin(argv));
	else
		return (first_cmd(argv, env, paths));
}

int	run_process_command(int first_pipe, int *new_pipe_fd,
char **p_cmd, char **env)
{
	pid_t	pid;

	if (fork_store(&pid) == -1)
		return (-1);
	else if (pid == 0)
		return (run_command(first_pipe, new_pipe_fd, p_cmd, env));
	return (0);
}

int	change_in_out(int arg_i, int first_pipe, char **argv, char **outfile)
{
	int	cmd_index;

	(void)first_pipe;
	cmd_index = -1;
	while (argv[arg_i] && ft_strcmp(argv[arg_i], "|") != 0)
	{
		if (ft_strcmp(argv[arg_i], ">") == 0)
			*outfile = argv[++arg_i];
		else
			cmd_index = arg_i;
		++arg_i;
		// 		else if (ft_strcmp(argv[arg_i], ">>") == 0)
		// 	first_pipe = append_iteration(&arg_i, first_pipe, argv);
	}
	printf("iD %d\n", cmd_index);
	return (cmd_index);
}

int	iter_pipes(int argc, char **argv, char **env, char **paths)
{
	int		first_pipe;
	int		new_pipe_fd[2];
	int		arg_i;
	char	**p_cmd;
	int		has_printed;
	char	*outfile;

	(void)argc;
	// first_pipe = get_first_pipe(argv, env, paths);
	first_pipe = 0;
	arg_i = 1;
	has_printed = 0;
	while (argv[arg_i] != NULL)
	{	
		has_printed = 1;
		outfile = NULL;
		arg_i = change_in_out(arg_i, first_pipe, argv, &outfile);
		// temp error management
		if (arg_i == -1)
			return 0;
		has_printed = 0;
		/* use excve on the cmd */
		p_cmd = parse_cmd(argv[arg_i], paths);
		if (pipe(new_pipe_fd) == -1 || first_pipe == -1)
			return (free_split_int(p_cmd));
		if (p_cmd)
		{
			if (run_process_command(first_pipe, new_pipe_fd, p_cmd, env) == -1)
				return (free_split_int(p_cmd));
		}
		if (dup2(new_pipe_fd[0], first_pipe) == -1)
			return (free_split_int(p_cmd));
		close_pipe(new_pipe_fd);
		free_split(p_cmd);
		/* end execution cmd (must be move in a function) */
		if (outfile)
		{
			has_printed = 0;
			first_pipe = write_command_output(first_pipe, outfile, 0);
		}
	}
	if (has_printed == 0)
		first_pipe = write_command_output(first_pipe, NULL, -1);
	close(first_pipe);
	return (1);
}
/* peut importe l'ordre pour < et > leur comportement est le suivant: > {file}
ces redirection n'ont d'impacte que si elles sont suivit d'une commande*/
/* the < addition themselves */
/* each > write on each files, same for >> */