/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 16:24:21 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/18 16:29:28 by pleveque         ###   ########.fr       */
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
int		open_store(int *fd_res, char *filename, int mode);;
int		change_in_out(int first_pipe, char **argv, t_str_tab **outfiles, t_str_tab **cmd_args);
int    	ft_strs_include(char *s, char **str);

/* MAIN */
int		first_cmd(char **argv, char **env, char **paths);
int		run_command(int entry_pipe, int	*pipe_fd, char **argv, char **env);
char	*parse_cmd(char *command, char **paths);
int		input_error(char *error_type, char	*precision, int type);
int		limited_stdin(char **argv);

/* WRITE */
int		write_fd_to_fd(int src_fd, int dst_fd);
int		write_command_output(char *dst, int fd);
int		iter_pipes(int argc, char **argv, char **env, char **paths);

#endif