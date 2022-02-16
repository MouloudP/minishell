/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:20:48 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/16 09:41:25 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	get_binary_path(char **cmd, char **path_split)
{
	int		i;
	char	*bin;

	i = -1;
	while (path_split[++i])
	{
		bin = ft_calloc(sizeof(char), (ft_strlen(path_split[i])
					+ 2 + ft_strlen(cmd[0])));
		if (!bin)
			break ;
		ft_strcat(bin, path_split[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmd[0]);
		if (access(bin, F_OK) == 0)
			break ;
		free(bin);
		bin = NULL;
	}
	free_str(path_split);
	free(cmd[0]);
	cmd[0] = bin;
}

void	get_absolute_path(char **cmd)
{
	char	*path;
	char	**path_split;

	path = ft_strdup(getenv("PATH"));
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		get_binary_path(cmd, path_split);
	}
	else
	{
		free(path);
		path = NULL;
	}
}

void	exec_cmd(char **cmd)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
		perror("Error de fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
			perror("Erreur du shell");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char **env)
{
	char	*line;
	t_m		mini;
	t_token	*cmd;

	(void) argc;
	(void) argv;
	setup_signal(&mini);
	get_env(env, &mini);
	line = readline("$> ");
	while (line)
	{
		add_history(line);
		if (line[0])
		{
			cmd = ft_partsing(line);
			if (cmd_built(cmd) == 0)
			{
				//get_absolute_path(cmd);
				//if (!cmd[0])
				//	ft_printf("Command not found !\n");
				//else
				//	exec_cmd(cmd);
			}
			//Faut ici free le cmd;
		}
		line = readline("$> ");
	}
	rl_clear_history();
}
