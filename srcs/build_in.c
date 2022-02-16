/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:14:42 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/16 14:46:48 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_mini_cd(char *path)
{
	char	*base;

	base = getenv("HOME");
	if (!path || ft_strlen(path) == 0)
		path = base;
	else if (ft_strncmp(path, "~", 1) == 0)
		path = ft_strjoin(base, path + 1);
	if (chdir(path) == -1)
		perror("cd");
	return (1);
}

int	ft_mini_pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	ft_printf("%s\n", s);
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

int	ft_mini_echo(char **str)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (str[i])
	{
		if (i == 1 && ft_strncmp(str[i], "-", 1) == 0 && ft_check_arg(str[i]))
		{
			n = 1;
			i++;
			if (!str[i])
				return (1);
			continue ;
		}
		ft_printf("%s", str[i]);
		i++;
		if (str[i])
			ft_printf(" ");
	}
	if (n == 0)
		ft_printf("\n");
	return (1);
}

int	cmd_built(t_token *cmd)
{
	if (ft_strcmp(cmd[0].value, "cd") == 0)
		return (ft_mini_cd(cmd[1].value));
	/*else if (ft_strcmp(cmd[0].value, "echo") == 0)
		return (ft_mini_echo(cmd));
	else if (ft_strcmp(cmd[0].value, "pwd") == 0)
		return (ft_mini_pwd());*/
	return (0);
}
