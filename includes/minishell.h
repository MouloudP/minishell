/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:16:16 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/22 16:21:26 by pleveque         ###   ########.fr       */
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
# include <token.h>
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

/// Parsing
t_token	*ft_partsing(char *str, t_m *mini);
t_token	*ft_realloc_cmd(t_token	*cmd, int size);
t_token	free_and_return(char *str, t_token token);
t_token	*ft_remove_cmd(t_token *cmd, int size, int del);
t_token	ft_getarg(char *str, int *i, t_m *mini);
void	ft_parse_token(t_token *token, t_m *mini);
int		ft_check_syntax(char *str);
void	ft_delimiters(char *s, t_token *token);

/// Mem gestion
char	*free_add_assign(char *str, char *news);
void	free_cmd(t_token *cmd);
void	free_env(t_m *mini);
void	free_env_bis(t_m *mini);
void	free_pipe(t_m *mini);
char	**ft_realloc(char **cmd, int size);

// Env
char	*ft_getenv(t_m *mini, char *var);
void	ft_setenv(t_m *mini, char *name, char *value, int init);
void	ft_removeenv(t_m *mini, char *name);
void	ft_printenv(t_m *mini, int out_fd);
void	ft_printexport(t_m *mini, int out_fd);
void	update_env(t_m *mini);
void	get_env(char **env, t_m *mini);

// Tools
int		ft_whitespace(char c);
int		ft_quote(char c);
int		ft_redirec(char c);
void	ft_exit_error(char *str, int num);

// Pipex
int		pipex(t_pipe *pipes, int pipe_size, char **env, t_m *mini);

// Signal
void	setup_signal(t_m *mini);
void	cancel_c(int sig);
void	cancel_c2(int sig);

/* UTILS */
char	**first_split(char *s, char c);

#endif