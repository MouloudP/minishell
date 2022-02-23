/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:24:21 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 10:55:51 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "get_next_line.h"
# include <../includes/token.h>

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
# define TOKEN_ERROR 10 // 
// cmd
# define VALID_CMD 1 // 
# define INVALID_CMD 3 // 
# define INVALID_FD -1 // 

typedef struct s_str_tab
{
	char	**str;
	int		size;
}	t_str_tab;

typedef struct s_stack
{
	int		*v;
	int		size;
}	t_stack;

/* PIPEx */
int		pipex(t_pipe *pipes, int pipe_size, char **env, t_m *mini);
int		iter_pipes(t_pipe *pipes, int pipe_size, t_m *mini);

/* UTILS */
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(char const *str);
char	**ft_split(char const *s, char c);
void	*free_split(char **splited);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strclen(char *str, char c);
int		ft_biggest(int a, int b);
int		ft_strcmp(char *str1, char *str2);
int		free_split_int(char **splitted);
void	close_pipe(int *pipe);
int		fork_store(pid_t *pid_res);
int		open_store(int *fd_res, char *filename, int mode);
int		redirections(t_pipe pipe, int *input_fd, int *output_fd);
int		ft_strs_include(char *s, char **str);
int		ft_tern(int condition, int a, int b);
char	*ft_strdupp(const char *s);
char	**get_paths(char **env);
char	**args_cpy(char **cmd, int size);

/* BUILTINS */
int		is_builtin(char *cmd);
int		run_builtin(char **cmd, t_m *mini, int fd_in, int fd_out);

/* MAIN */
int		run_command(int entry_pipe, int	*pipe_fd, char **argv, t_m *mini);
int		run_process_command(int first_pipe, char **pipe_cmd,
			t_m *mini, int *new_pipe_fd);
int		parse_cmd(char **command, char **paths);
int		input_error(char *error_type, char	*precision, int type);
int		limited_stdin(char **argv);

/* WRITE */
int		write_fd_to_fd(int src_fd, int dst_fd);
int		write_command_output(char *dst, int fd);
int		open_output(char *outfile, int append);

#endif
