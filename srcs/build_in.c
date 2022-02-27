/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:14:42 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/27 17:39:37 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mini_cd(char **cmd, t_m *mini)
{
	char	*base;
	char	*ph;
	int		fre;

	fre = 0;
	base = ft_getenv(mini, "HOME");
	ph = cmd[1];
	if (!ph || ft_strlen(ph) == 0)
		ph = base;
	else if (ft_strncmp(ph, "~", 1) == 0 && base && ++fre)
		ph = ft_strjoin(base, ph + 1);
	if (cmd[1] && cmd[2])
		return (free_pwd(ph, fre), write(1, "cd : too many arguments\n", 24), 2);
	if (!ph || ft_strlen(ph) == 0 || !ft_getenv(mini, "PWD"))
		return (write(2, "cd : Environement unvailable\n", 29), 2);
	else if (chdir(ph) == -1)
		return (perror("cd"), 2);
	else
		ft_go_cd(mini, ph);
	return (free_pwd(ph, fre), EXIT_SUCCESS);
}

int	ft_mini_pwd(char **cmd, int fd_out)
{
	char	cwd[1024];

	(void) cmd;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		write(fd_out, cwd, ft_strlen(cwd));
		write(fd_out, "\n", 1);
		return (EXIT_SUCCESS);
	}
	else
		perror("pwd\n");
	return (EXIT_FAILURE);
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
				return (EXIT_SUCCESS);
			continue ;
		}
		write(fd_out, cmd[i], ft_strlen(cmd[i]));
		i++;
		if (cmd[i] && ft_strlen(cmd[i - 1]) > 0)
			write(fd_out, " ", 1);
	}
	if (n == 0)
		write(fd_out, "\n", 1);
	return (EXIT_SUCCESS);
}

int	ft_mini_env(t_m *mini, int fd_out)
{
	ft_printenv(mini, fd_out);
	return (EXIT_SUCCESS);
}
