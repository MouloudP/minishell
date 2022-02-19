/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:16:16 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/19 16:12:49 by ahamdoun         ###   ########.fr       */
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
# define TOKEN_NULL 0
# define TOKEN_COMMAND 1
# define TOKEN_ARGUMENT 2
# define TOKEN_PIPE 3
# define TOKEN_REDIRECTION_INPUT 4 // >
# define TOKEN_REDIRECTION_OUTPUT 5 // <
# define TOKEN_REDIRECTION_APPEND 6 // >>
# define TOKEN_REDIRECTION_DELIMTER 7 // <<
# define TOKEN_REDIRECTION_OTHER 8 // <>
# define TOKEN_FILE 9
# define TOKEN_ERROR 10 // >< Error de parsing || &&

typedef struct s_env // LENv du minishell
{
	char	*name;
	char	*value;
	int		init;
}	t_env;

typedef struct s_m // La struc du minishell
{
	void	(*signal_save)(int);
	t_env	*env;
	int		env_lenght;
	int		end;
}	t_m;

typedef struct s_token // Parsing au départ des éléments
{
	int		type;
	char	*value;
	t_m		mini;
}	t_token;

typedef struct s_pipe // Parsing par pipe pour le Pierro
{
  t_token	*cmd;
  char		**parse_cmd;
  int		cmd_count;
  t_token	*infile;
  int		infile_count;
  t_token	*outfile;
  int		outfile_count;
}  t_pipe;

t_token	*ft_partsing(char *str);
t_token	free_and_return(char *str, t_token token);
void    ft_parse_token(t_token	*token);

char	*free_add_assign(char *str, char *news);
void	free_cmd(t_token *cmd);
void	free_env(t_m *mini);
char	**ft_realloc(char **cmd, int size);

char	*ft_getenv(t_m *mini, char *var);
void	ft_setenv(t_m *mini, char *name, char *value, int init);
void	ft_printenv(t_m *mini);
void	ft_printexport(t_m *mini);

int		cmd_built(t_token *cmd, t_m *mini);
void	setup_signal(t_m *mini);
void	get_env(char **env, t_m *mini);


int		ft_whitespace(char c);
int		ft_quote(char c);
int		ft_redirec(char c);
#endif