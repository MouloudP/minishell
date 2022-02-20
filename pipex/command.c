/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:13:26 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/20 16:13:11 by pleveque         ###   ########.fr       */
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
		run_builtin(parsed_cmd, mini);
		exit(0);
	}
	if (execve(parsed_cmd[0], &parsed_cmd[0], mini->env_bis) == -1)
		input_error("Command execution", parsed_cmd[0], 0);
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

int		is_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		++i;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}

int	parse_cmd(char **command, char **paths)
{
	int		i;
	char	*full_path;

	(void)full_path;
	if (!*command)
		return (-1);
	if (is_path(*command))
	{
		if (access(*command, F_OK | X_OK) == 0)
			return (1);
		input_error("Invalid path", *command, 2);
		return (-3);
	}
	if (is_builtin(*command) == 1)
		return(1);
	i = -1;
	while (paths[++i] != NULL)
	{
		full_path = create_path(paths[i], *command);
		if (!full_path)
		 	return (-2);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			*command = full_path;
			return (1);
		}
		free(full_path);
	}
	input_error("Invalid command", *command, 2);
	return (3);
}
