/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:50:05 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 19:42:18 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_pipe1(t_token *token, t_pipe *pipe, int i, int *j)
{
	if (token[*j].type == TOKEN_ARGUMENT
		|| token[*j].type == TOKEN_COMMAND)
		pipe[i].cmd_count++;
	else if (token[*j].type >= TOKEN_REDIRECTION_INPUT
		&& token[*j].type <= TOKEN_REDIRECTION_OTHER)
	{
		if (token[*j].type != TOKEN_REDIRECTION_DELIMTER)
			(*j)++;
		pipe[i].files_count++;
	}
	(*j)++;
}

t_pipe	*ft_create_pipe(t_token *token, int count)
{
	t_pipe	*pipe;
	int		i;
	int		j;
	int		n;

	pipe = ft_malloc(sizeof(t_pipe) * (count + 1));
	i = 0;
	j = 0;
	while (i < count)
	{
		pipe[i].cmd_count = 0;
		pipe[i].files_count = 0;
		n = j;
		while (token[j].value && token[j].type != TOKEN_PIPE)
			ft_create_pipe1(token, pipe, i, &j);
		ft_add_pipe(token, pipe, i, n);
		if (token[j].type == TOKEN_PIPE)
			j++;
		i++;
	}
	return (pipe);
}

void	ft_parse_token1(t_pipe *pipe, t_m *mini, int count)
{
	int	i;
	int	j;

	i = 0;
	pipe[i].parse_cmd = NULL;
	while (i < count)
	{
		pipe[i].parse_cmd = ft_malloc(sizeof(char *) * (pipe[i].cmd_count + 1));
		j = 0;
		while (j < pipe[i].cmd_count)
		{
			pipe[i].parse_cmd[j] = pipe[i].cmd[j].value;
			j++;
		}
		pipe[i].parse_cmd[j] = NULL;
		i++;
	}
	mini->pipe = pipe;
	mini->pipe_lenght = count;
}

int	ft_check_token_syntax(t_token *token, int i)
{
	if (i > 0 && token[i - 1].type == TOKEN_PIPE)
		return (1);
	i = 0;
	while (token[i].value)
	{
		if (token[i].type >= 4 && token[i].type <= 8
			&& token[i].type != TOKEN_REDIRECTION_DELIMTER)
		{
			if (!token[i + 1].value || token[i + 1].type != TOKEN_FILE)
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_parse_token(t_token *token, t_m *mini)
{
	int		i;
	int		count;
	t_pipe	*pipe;

	i = 0;
	count = 0;
	while (token[i].value)
	{
		ft_parse_start(token, &i);
		count++;
		if (token[i].value && token[i].type == TOKEN_PIPE)
			i++;
	}
	pipe = ft_create_pipe(token, count);
	ft_parse_token1(pipe, mini, count);
	if (ft_check_token_syntax(token, i))
	{
		write(2, "Minishell : syntax error\n", 25);
		mini->exit_status = 2;
		return ;
	}
	if (mini->canceldelimiters != 0 || count <= 0)
		return ;
	pipex(pipe, count, mini->env_bis, mini);
}
