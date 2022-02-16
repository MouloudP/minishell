/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 16:59:01 by pleveque          #+#    #+#             */
/*   Updated: 2022/01/20 12:34:31 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Read the first command with argv and send back what was readed
even if nothing was readed due to a bad command */

int	first_cmd(char **argv, char **env, char **paths)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		new_entry;
	char	**parsed_cmd;

	if (pipe(pipe_fd) == -1)
		return (-1);
	parsed_cmd = parse_cmd(argv[2], paths);
	if (!parsed_cmd)
	{
		close(pipe_fd[1]);
		return (pipe_fd[0]);
	}
	if (open_store(&new_entry, argv[1], O_RDONLY) == -1)
		return (free_split_int(parsed_cmd));
	pid = fork();
	if (pid == -1 || new_entry == -1)
		return (free_split_int(parsed_cmd));
	if (pid == 0)
		if (run_command(new_entry, pipe_fd, parsed_cmd, env) == -1)
			return (free_split_int(parsed_cmd));
	close(new_entry);
	close(pipe_fd[1]);
	free_split(parsed_cmd);
	return (pipe_fd[0]);
}

/* read the stdin and write on a pipe until a line is 
equal to the limiter or stdin is close. Return the pipe entry*/

int	limited_stdin(char **argv)
{
	char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		return (-1);
	line = NULL;
	while (1)
	{
		line = get_next_line(0);
		if (!line || ft_strncmp(line, argv[2],
				ft_biggest(ft_strlen(argv[2]), ft_strclen(line, '\n'))) == 0)
		{
			if (line)
				free(line);
			close(pipe_fd[1]);
			return (pipe_fd[0]);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	return (-1);
}
