#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_env // LENv du minishell
{
	char	*name;
	char	*value;
	int		init;
}	t_env;

typedef struct s_m // La struc du minishell
{
	void			(*signal_save)(int);
	void			(*cancel_c)(int);
	void			(*cancel_c2)(int);
	t_env			*env;
	char			**env_bis;
	int				env_lenght;
	struct s_pipe	*pipe;
	int				pipe_lenght;
	int				end;
	int				exit_status;
}	t_m;

typedef struct s_token // Parsing au départ des éléments
{
	int		type;
	char	*value;
	int		fd;
	int		env;
    t_m     mini;
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

/* BUILTS IN */
int	    ft_mini_cd(char **cmd, t_m *mini);
int		ft_mini_pwd(char **cmd, int out_fd);
int		ft_exit(t_m *mini);
int		ft_mini_env(t_m *mini, int out_fd);
int		ft_mini_echo(char **cmd, int out_fd);
int		ft_mini_export(char **cmd, t_m *mini, int out_fd);
int		ft_mini_unset(char **cmd, t_m *mini);

#endif