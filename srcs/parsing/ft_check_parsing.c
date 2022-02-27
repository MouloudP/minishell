/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 15:26:50 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/27 18:22:33 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getquote(char *str, int *i, char c, t_m *mini)
{
	char	*arg;
	char	*s;

	arg = ft_calloc(sizeof(char), 1);
	s = ft_calloc(sizeof(char), 2);
	while (str[*i] && str[*i] != c)
	{
		if (str[*i] == '\\' && str[(*i + 1)] != c)
			(*i)++;
		s[0] = str[*i];
		arg = ft_fa(arg, ft_strjoin(arg, s));
		(*i)++;
	}
	free(s);
	arg = ft_quote_env(arg, c, mini);
	return (arg);
}

int	ft_get_redirection(char *s)
{
	if (ft_strcmp(s, ">") == 0)
		return (TOKEN_REDIRECTION_INPUT);
	else if (ft_strcmp(s, "<") == 0)
		return (TOKEN_REDIRECTION_OUTPUT);
	else if (ft_strcmp(s, ">>") == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (ft_strcmp(s, "<<") == 0)
		return (TOKEN_REDIRECTION_DELIMTER);
	else if (ft_strcmp(s, "<>") == 0)
		return (TOKEN_ERROR);
	return (TOKEN_ERROR);
}

t_token	ft_redirection(char *str, char c, int *i, t_m *mini)
{
	t_token	token;
	t_token	temp;

	ft_reset_token(&token);
	if (str[*i + 1] && (ft_redirec(str[*i + 1])))
	{
		token.value = ft_strndup(str + *i, 2);
		if (c == '>' && str[*i + 1] == '<')
			token.type = TOKEN_ERROR;
		else
			token.type = ft_get_redirection(token.value);
		*i = *i + 2;
		if (token.type == TOKEN_REDIRECTION_DELIMTER)
		{
			while (str[(*i)] && ft_whitespace(str[(*i)]))
				(*i)++;
			temp = ft_getarg(str, i, mini, 0);
			if (mini->canceldelimiters == 0)
				ft_delimiters(temp.value, &token, mini, ft_expand(str[*i - 1]));
			free(temp.value);
		}
	}
	else
		ft_set_token(&token, c, -10, (*i)++);
	return (token);
}

t_token	ft_pipe(char *str, char c, int *i)
{
	t_token	token;

	token.env = 0;
	token.type = 0;
	if (str[*i + 1] && (c == str[*i + 1]))
	{
		token.value = ft_strndup(str + *i, 2);
		token.type = TOKEN_ERROR;
		*i = *i + 2;
	}
	else
	{
		token.value = ft_malloc(sizeof(char) * 2);
		token.value[0] = c;
		token.value[1] = '\0';
		token.type = TOKEN_PIPE;
		(*i)++;
	}
	return (token);
}

t_token	*ft_partsing(char *str, t_m *mini)
{
	int		i;
	int		j;
	t_token	*cmd;
	t_token	temp;

	cmd = ft_malloc(sizeof(t_token) * 1);
	i = 0;
	while (str[i] && ft_whitespace(str[i]))
		i++;
	j = 0;
	while (str[i])
	{
		temp = ft_getarg(str, &i, mini, 0);
		if (temp.value)
		{
			cmd = ft_realloc_cmd(cmd, j);
			cmd[j++] = temp;
		}
		while (str[i] && ft_whitespace(str[i]))
			i++;
	}
	ft_reset_token2(&cmd[j]);
	cmd = ft_parse_env(cmd, mini, j);
	ft_parse_token(cmd, mini);
	return (cmd);
}
