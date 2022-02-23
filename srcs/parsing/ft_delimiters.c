/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delimiters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:38:23 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 12:15:32 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delimiters2(char **line, char *s, char *temp, char **ret)
{
	free(*line);
	*line = readline("\e[0;35m>\e[0;37m ");
	if (*line && *line[0] && ft_strcmp(*line, s) != 0)
	{
		temp = *ret;
		*ret = ft_strjoin(*ret, *line);
		free(temp);
		temp = *ret;
		*ret = ft_strjoin(*ret, "\n");
		free(temp);
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

void	ft_delimiters(char *s, t_token *token, t_m *mini)
{
	char	*line;
	char	*ret;
	char	*temp;
	int		pipes[2];

	if (pipe(pipes) == -1)
	{
		perror("pipe");
		return ;
	}
	ret = ft_calloc(sizeof(char), 1);
	line = ft_calloc(sizeof(char), 1);
	temp = NULL;
	signal(SIGINT, cancel_c3);
	mini->dup_fd = dup(0);
	while (line && ft_strcmp(line, s) != 0 && mini->canceldelimiters == 0)
		ft_delimiters2(&line, s, temp, &ret);
	if (mini->canceldelimiters)
		return ;
	if (line)
		free(line);
	ft_delimiters1(ret, s, pipes, token);
}
