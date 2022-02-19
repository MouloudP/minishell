/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 19:13:26 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/19 12:31:55 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*parse_cmd(char *command, char **paths)
{
	int		i;
	char	*full_path;

	(void)full_path;
	if (!command)
		return (NULL);
	i = -1;
	while (paths[++i] != NULL)
	{
		full_path = create_path(paths[i], command);
		if (!full_path)
		 	return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
	}
	if (access(command, F_OK | X_OK) == 0)
		return (command);	
	input_error("Invalid command\n", command, 2);
	return (NULL);
}
