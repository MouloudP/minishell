/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:16:16 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/17 16:08:38 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <libft.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char	*name;
	char	*value;
	int		init;
}	t_env;

typedef struct s_m
{
	void	(*signal_save)(int);
	t_env	*env;
	int		env_lenght;
}	t_m;

typedef struct s_token
{
	char	*type;
	char	*value;
	t_m		mini;
}	t_token;

t_token	*ft_partsing(char *str);
char	*free_add_assign(char *str, char *news);
void	free_cmd(t_token *cmd);
void	free_env(t_m *mini);
char	**ft_realloc(char **cmd, int size);

char	*ft_getenv(t_m *mini, char *var);
void	ft_setenv(t_m *mini, char *name, char *value);
void	ft_printenv(t_m *mini);

int		cmd_built(t_token *cmd, t_m *mini);
void	setup_signal(t_m *mini);
void	get_env(char **env, t_m *mini);


#endif