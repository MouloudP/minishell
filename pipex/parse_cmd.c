/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 10:11:35 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/22 14:39:34 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	is_path(char *cmd)
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

int	parse_cmd(char **command, char **paths)
{
	int		i;
	char	*full_path;

	if (!*command)
		return (-1);
	if (is_path(*command))
	{
		if (access(*command, F_OK | X_OK) == 0)
			return (*command = ft_strdupp(*command), VALID_CMD);
		input_error("Invalid path", *command, 2);
		return (-3);
	}
	if (is_builtin(*command) == 1)
		return (*command = ft_strdupp(*command), VALID_CMD);
	i = -1;
	while (paths[++i] != NULL)
	{
		full_path = create_path(paths[i], *command);
		if (!full_path)
			return (-2);
		if (access(full_path, F_OK | X_OK) == 0)
			return (*command = full_path, VALID_CMD);
		free(full_path);
	}
	return (input_error("Invalid command", *command, 2), INVALID_CMD);
}
