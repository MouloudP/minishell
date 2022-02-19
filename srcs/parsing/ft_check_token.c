/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:26:44 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/19 19:53:07 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_print_token(t_token *token)
{
	int i;

	i = 0;
	while (token[i].value)
	{
		if (token[i].type == 1)
			ft_printf("[%d] TYPE : %s | VALUE : %s\n", i, "COMMAND", token[i].value);
		else if (token[i].type == 2)
			ft_printf("[%d] TYPE : %s | VALUE : %s\n", i, "ARGUMENT", token[i].value);
		else if (token[i].type == 3)
			ft_printf("[%d] TYPE : %s | VALUE : %s\n", i, "PIPE", token[i].value);
		else if (token[i].type >= 4 && token[i].type <= 8)
			ft_printf("[%d] TYPE : %s | VALUE : %s\n", i, "REDIRECTION", token[i].value);
		else if (token[i].type == 9)
			ft_printf("[%d] TYPE : %s | VALUE : %s\n", i, "FILE", token[i].value);
		else if (token[i].type == 10)
			ft_printf("[%d] TYPE : %s | VALUE : %s\n", i, "ERROR", token[i].value);
		i++;
	}
}

void    ft_parse_start(t_token *token, int *i)
{
	int cmd;

	cmd = 1;
	while (token[*i].value && token[*i].type != TOKEN_PIPE) // On va jusquau pipe
	{
		if (token[*i].type >= 4 && token[*i].type <= 8) // Si on a une redirection le prochain argument est un FILE
		{
			(*i)++;
			token[*i].type = TOKEN_FILE;
		}
		else if (cmd && token[*i].type == TOKEN_ARGUMENT)
		{
			token[*i].type = TOKEN_COMMAND;
			cmd = 0;
		}
		(*i)++;
	}
}

t_token	ft_copy_token(t_token token)
{
	t_token copy;

	copy.value = token.value;
	copy.type = token.type;
	return (copy);
}

void    ft_add_pipe(t_token *token, t_pipe *pipe, int i, int j)
{
	ft_printf("START J : %d | PIPE : %d\n", j, i);
	pipe[i].cmd = malloc(sizeof(t_token) * (pipe[i].cmd_count + 2));
	pipe[i].infile = malloc(sizeof(t_token) * (pipe[i].infile_count + 2));
	pipe[i].outfile = malloc(sizeof(t_token) * (pipe[i].outfile_count + 2));
	pipe[i].cmd_count = 0;
	pipe[i].infile_count = 0;
	pipe[i].outfile_count = 0;
	while (token[j].type && token[j].type != TOKEN_PIPE)
	{
		if (token[j].type == TOKEN_ARGUMENT || token[j].type == TOKEN_COMMAND)
		{
			pipe[i].cmd[pipe[i].cmd_count++] = ft_copy_token(token[j]);
		}
		else if (token[j].type == TOKEN_REDIRECTION_INPUT || token[j].type == TOKEN_REDIRECTION_APPEND)
		{
			pipe[i].outfile[pipe[i].outfile_count] = ft_copy_token(token[++j]);
			pipe[i].outfile[pipe[i].outfile_count].type = token[j - 1].type;
			pipe[i].outfile_count++;
		}
		else if (token[j].type == TOKEN_REDIRECTION_OUTPUT || token[j].type == TOKEN_REDIRECTION_OTHER || token[j].type == TOKEN_REDIRECTION_DELIMTER)
		{
			pipe[i].infile[pipe[i].infile_count] = ft_copy_token(token[++j]);
			pipe[i].infile[pipe[i].infile_count].type = token[j - 1].type;
			pipe[i].infile_count++;
		}
		j++;
	}
}

t_pipe	*ft_create_pipe(t_token *token, int count)
{
	t_pipe	*pipe;
	int		i;
	int     j;
	int		n;

	pipe = malloc(sizeof(t_pipe) * (count + 1));
	i = 0;
	j = 0;
	while (i < count)
	{
		pipe[i].cmd_count = 0;
		pipe[i].infile_count = 0;
		pipe[i].outfile_count = 0;
		n = j;
		while (token[j].type && token[j].type != TOKEN_PIPE)
		{
			if (token[j].type == TOKEN_ARGUMENT || token[j].type == TOKEN_COMMAND)
				pipe[i].cmd_count++;
			else if (token[j].type == TOKEN_REDIRECTION_INPUT || token[j].type == TOKEN_REDIRECTION_APPEND)
			{
				j++;
				//token[j].type = token[j - 1].type;
				pipe[i].outfile_count++;
			}
			else if (token[j].type == TOKEN_REDIRECTION_OUTPUT || token[j].type == TOKEN_REDIRECTION_OTHER || token[i].type == TOKEN_REDIRECTION_DELIMTER)
			{
				j++;
				//token[i].type = token[i - 1].type;
				pipe[i].infile_count++;
			}
			j++;
		}
		ft_add_pipe(token, pipe, i, n);
		if (token[j].type == TOKEN_PIPE)
			j++;
		i++;
	}
	return (pipe);
}

void    ft_parse_token(t_token *token, t_m *mini) // On va assigner les cmd
{
	int		i;
	int		j;
	int		count;
	t_pipe	*pipe;
	//int redirec;

	i = 0;
	count = 0;
	//redirec = 1;
	while (token[i].value)
	{
		ft_parse_start(token, &i);
		count++;
		i++;
	}
	ft_print_token(token);
	pipe = ft_create_pipe(token, count);
	i = 0;
	j = 0;
	while (i < count)
	{
		ft_printf("PIPE : %d\n \tCOMMANDE : \n\t\t", i);
		j = 0;
		while (j < pipe[i].cmd_count)
		{
			ft_printf("%s ", pipe[i].cmd[j].value);
			j++;
		}
		ft_printf("\n\tINFILE :\n\t\t");
		j = 0;
		while (j < pipe[i].infile_count)
		{
			ft_printf("%s ", pipe[i].infile[j].value);
			j++;
		}
		ft_printf("\n\tOUTFILE :\n\t\t");
		j = 0;
		while (j < pipe[i].outfile_count)
		{
			ft_printf("%s ", pipe[i].outfile[j].value);
			j++;
		}
		ft_printf("\n");
		//ft_printf("|%d| : \n %s", count, pipe[i].cmd[0].value);
		i++;
	}
	i = 0;
	while (i < count)
	{
		pipe[i].parse_cmd = malloc(sizeof(char *) * (pipe[i].cmd_count + 1));
		j = 0;
		while (j < pipe[i].cmd_count)
		{
			pipe[i].parse_cmd[j] = pipe[i].cmd[j].value;
			j++;
		}
		pipe[i].parse_cmd[j] = NULL;
		i++;
	}
	pipex(pipe, count, mini->env_bis);
}

/*pipes = {
	cmd = {
		[0] = echo
		[1] = bonsoir
		[2] = paris
		[3] = NULL
	}
	size = 3
	t_token = tokens
}*/

/*t_pipe = 
{
	[0] = {
		cmd = {
			[0] = cat
			[1] = Makefile
			[2] = Makefile
			[3] = Makefile
		}
		infile = {
			[0] = file2
		}
		output = {
			[0] = file
		}
	}
}*/