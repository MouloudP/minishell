/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:32:00 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 11:46:54 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_token(t_token *token, char c, int type, int i)
{
	token->value = malloc(sizeof(char) * 2);
	token->value[0] = c;
	token->value[1] = '\0';
	if (type != -10)
		token->type = type;
	else
		token->type = ft_get_redirection(token->value);
	(void) i;
}

void	ft_reset_token(t_token *token)
{
	token->env = 0;
	token->type = 0;
	token->fd = 0;
}

void	ft_reset_token2(t_token *token)
{
	token->type = TOKEN_NULL;
	token->value = NULL;
}
