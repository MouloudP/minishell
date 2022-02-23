/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gerarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:41:15 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 11:12:50 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	ft_redirec_arg(t_get_arg arg, t_token token, int *i, char *str)
{
	if (ft_strlen(token.value) >= 1)
		return (free_and_return(arg.s, token));
	else
	{
		return (free_and_return(token.value,
				free_and_return(arg.s,
					ft_redirection(str, str[*i], i, arg.mini))));
	}
}

t_token	ft_pipe_arg(t_get_arg arg, t_token token, int *i, char *str)
{
	if (ft_strlen(token.value) >= 1)
		return (free_and_return(arg.s, token));
	else
		return (free_and_return(token.value,
				free_and_return(arg.s,
					ft_pipe(str, str[*i], i))));
}

void	ft_quote_arg(t_get_arg arg, t_token *token, int *i, char *str)
{
	(*i)++;
	token->type = TOKEN_ARGUMENT;
	arg.temp = ft_getquote(str, i, str[*i - 1], arg.mini);
	token->value = ft_fa(token->value,
			ft_strjoin(token->value, arg.temp));
	free(arg.temp);
}

void	ft_set_base(t_token *token, t_get_arg *arg, t_m *mini)
{
	token->value = ft_calloc(sizeof(char), 1);
	token->env = 0;
	token->fd = 0;
	arg->s = ft_calloc(sizeof(char), 2);
	arg->mini = mini;
}

t_token	ft_getarg(char *str, int *i, t_m *mini)
{
	t_token		token;
	t_get_arg	arg;

	ft_set_base(&token, &arg, mini);
	while (str[*i] && !ft_whitespace(str[*i]))
	{
		if (ft_quote(str[*i]))
			ft_quote_arg(arg, &token, i, str);
		else
		{
			if (str[*i] == '\\')
				(*i)++;
			else if (ft_redirec(str[*i]))
				return (ft_redirec_arg(arg, token, i, str));
			else if (str[*i] == '|')
				return (ft_pipe_arg(arg, token, i, str));
			else if (str[*i] == '$')
				token.env = 1;
			arg.s[0] = str[*i];
			token.type = TOKEN_ARGUMENT;
			token.value = ft_fa(token.value, ft_strjoin(token.value, arg.s));
		}
		(*i)++;
	}
	return (free_and_return(arg.s, token));
}
