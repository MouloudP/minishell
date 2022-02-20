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
	t_env			*env;
	char			**env_bis;
	int				env_lenght;
	struct s_pipe	*pipe;
	int				pipe_lenght;
	int				end;
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

#endif