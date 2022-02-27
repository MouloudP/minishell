/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delimiters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:38:23 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/27 10:41:06 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delimiters2(t_delimiters *del, char *s, int expand)
{
	del->temp = NULL;
	free(del->line);
	del->line = readline("\e[0;35m>\e[0;37m ");
	if (del->line && ft_strcmp(del->line, s) != 0)
	{
		if (!expand)
			del->line = ft_quote_env(del->line, '"', del->mini);
		del->temp = del->ret;
		del->ret = ft_strjoin(del->ret, del->line);
		free(del->temp);
		del->temp = del->ret;
		del->ret = ft_strjoin(del->ret, "\n");
		free(del->temp);
	}
}

void	ft_delimiters1(char *ret, char *s, int *pipes, t_token *token)
{
	write(pipes[1], ret, ft_strlen(ret));
	close(pipes[1]);
	token->fd = pipes[0];
	token->value = ft_fa(token->value, ft_strdup(s));
	free(ret);
}

void	ft_delimiters(char *s, t_token *token, t_m *mini, int expand)
{
	t_delimiters	del;
	int				pipes[2];

	if (pipe(pipes) == -1)
	{
		perror("pipe");
		return ;
	}
	del.ret = ft_calloc(sizeof(char), 1);
	del.line = ft_calloc(sizeof(char), 1);
	del.mini = mini;
	signal(SIGINT, cancel_c3);
	mini->dup_fd = dup(0);
	del.start = 1;
	while (del.start || (del.line && ft_strcmp(del.line, s) != 0
			&& mini->canceldelimiters == 0))
	{
		del.start = 0;
		ft_delimiters2(&del, s, expand);
	}
	if (mini->canceldelimiters)
		return ;
	if (del.line)
		free(del.line);
	ft_delimiters1(del.ret, s, pipes, token);
}
