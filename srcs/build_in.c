/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:14:42 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/20 15:36:35 by pleveque         ###   ########.fr       */
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

int	ft_mini_pwd(char **cmd)
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
		ft_printf("%s\n", cwd); // faut join le HOME Au pwd
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

int	ft_mini_echo(t_token *cmd)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	while (cmd[i].type && cmd[i].type == TOKEN_ARGUMENT)
	{
		if (i == 1 && ft_strncmp(cmd[i].value, "-", 1) == 0 && ft_check_arg(cmd[i].value))
		{
			n = 1;
			i++;
			if (!cmd[i].type)
				return (1);
			continue ;
		}
		ft_printf("%s", cmd[i].value);
		i++;
		if (cmd[i].type && cmd[i].type == TOKEN_ARGUMENT)
			ft_printf(" ");
	}
	if (n == 0)
		ft_printf("\n");
	return (1);
}

int	ft_mini_export(t_token *cmd, t_m *mini)
{
	if (cmd[1].value && cmd[2].value)
		ft_setenv(mini, cmd[1].value, cmd[2].value, 1);
	else if (cmd[1].value)
		ft_setenv(mini, cmd[1].value, NULL, 0);
	else
		ft_printexport(mini);
	return (1);
}

int	ft_mini_env(t_m *mini)
{
	ft_printenv(mini);
	return (1);
}

int	ft_exit(t_m *mini)
{
	mini->end = 0;
	return (1);
}

int	cmd_built(t_token *cmd, t_m *mini)
{
	(void)cmd;
	(void)mini;
	// if (ft_strcmp(cmd[0].value, "cd") == 0)
	// 	return (ft_mini_cd(cmd, mini));
	// else if (ft_strcmp(cmd[0].value, "echo") == 0)
	// 	return (ft_mini_echo(cmd));
	// else if (ft_strcmp(cmd[0].value, "pwd") == 0)
	// 	return (ft_mini_pwd(cmd));
	// else if (ft_strcmp(cmd[0].value, "export") == 0)
	// 	return (ft_mini_export(cmd, mini));
	// else if (ft_strcmp(cmd[0].value, "env") == 0)
	// 	return (ft_mini_env(mini));
	// else if (ft_strcmp(cmd[0].value, "exit") == 0)
	// 	return	(ft_exit(mini));
	return (0);
}
