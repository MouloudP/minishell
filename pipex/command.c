/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:13:26 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/16 18:05:28 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_command_output(int pipe_fd, char *output, int add_to)
{
	char	buffer[1023];
	int		ret;
	int		fd;

	if (add_to == -1)
		fd = 1;
	else
	{
		if (!output)
			return (input_error("parse error near '\\n'", NULL, 0));
		fd = open(output, O_RDWR | O_CREAT, S_IRWXU);
		if (fd == -1)
			return (input_error("cant open fd", NULL, 0));
		close(fd);
		if (add_to == 0)
			unlink(output);
		fd = open(output, O_RDWR | O_CREAT, S_IRWXU);
		if (fd == -1)
			return (input_error("cant open fd", NULL, 0));
		ret = 1023;
		while (ret == 1023)
			ret = read(fd, buffer, 1023);
	}
	ret = 1;
	while (ret > 0)
	{
		ret = read(pipe_fd, buffer, 1023);
		write(fd, buffer, ret);
	}
	close(fd);
	if (add_to != -1)
	{
		close(pipe_fd);
		fd = open(output, O_RDWR | O_CREAT, S_IRWXU);
		return (fd);
	}
	return (pipe_fd);
}

/* close all the open fd */

int	run_command(int entry_pipe, int	*pipe_fd, char **parsed_cmd, char **env)
{
	if (dup2(entry_pipe, 0) == -1 || dup2(pipe_fd[1], 1) == -1)
		return (-1);
	close_pipe(pipe_fd);
	if (entry_pipe != 0)
		close(entry_pipe);
	if (!parsed_cmd)
		perror("split error");
	if (execve(parsed_cmd[0], &parsed_cmd[0], env) == -1)
		perror("execve");
	return (-1);
}

char	*create_path(char *path, char *filename)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, filename);
	free(tmp);
	return (full_path);
}

void	*replace_and_free(void *src, void *dst)
{
	free(dst);
	return (src);
}

char	**parse_cmd(char *command, char **paths)
{
	char	**parsed_cmd;
	int		i;
	char	*full_path;

	parsed_cmd = ft_split(command, ' ');
	if (!parsed_cmd)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		full_path = create_path(paths[i], parsed_cmd[0]);
		if (!full_path)
			return (free_split(parsed_cmd));
		if (access(full_path, F_OK | X_OK) == 0)
		{
			parsed_cmd[0] = replace_and_free(full_path, parsed_cmd[0]);
			return (parsed_cmd);
		}
		free(full_path);
	}
	if (access(parsed_cmd[0], F_OK | X_OK) == 0)
		return (parsed_cmd);
	input_error("Invalid command\n", parsed_cmd[0], 2);
	free_split(parsed_cmd);
	return (NULL);
}
