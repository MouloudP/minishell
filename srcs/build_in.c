/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:14:42 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/21 16:32:28 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mini_cd(char **cmd, t_m *mini)
{
	char	*base;
	char	*path;
	char 	cwd[1024];

	base = ft_getenv(mini, "HOME");
	path = cmd[1];
	if (!path || ft_strlen(path) == 0)
		path = base;
	else if (ft_strncmp(path, "~", 1) == 0 && base)
		path = ft_strjoin(base, path + 1);
	//ft_printf("JE VEUX ALLEZ LÀ : %s\n", path);
	if (chdir(path) == -1)
		perror("cd");
	else
	{
		//if (ft_printf("MAIS JE ME RETROUVE ICI : %s\n", getcwd(cwd, sizeof(cwd))))
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			ft_setenv(mini, "OLDPWD", ft_getenv(mini, "PWD"), 1); // faut join le HOME Au pwd
			ft_setenv(mini, "PWD", path, 1);
		}
	}
	return (1);
}

int	ft_mini_pwd(char **cmd, int fd_out)
{
	char 	cwd[1024];
	int		i;

	i = 1;
	while (cmd[i]) // Faut check le nombre darg
		i++;
	if (i > 1)
	{
		ft_printf("pwd: too many arguments\n"); // Il faut faire un print dans le stderror
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(fd_out, cwd, ft_strlen(cwd));
		write(fd_out, "\n", 1);
	}
	else
		perror("pwd\n"); // Afficher sur le stderror
	return (1);
}

int	ft_check_arg(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

int	ft_mini_echo(char **cmd, int fd_out)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i])
	{
		if (i == 1 && ft_strncmp(cmd[i], "-", 1) == 0 && ft_check_arg(cmd[i]))
		{
			n = 1;
			i++;
			if (!cmd[i])
				return (1);
			continue ;
		}
		write(fd_out, cmd[i], ft_strlen(cmd[i]));
		i++;
		if (cmd[i])
			write(fd_out, " ", 1);
	}
	if (n == 0)
		write(fd_out, "\n", 1);
	return (1);
}

int	ft_mini_env(t_m *mini, int fd_out)
{
	ft_printenv(mini, fd_out);
	return (1);
}

int	ft_exit(t_m *mini)
{
	mini->end = 0;
	return (1);
}
