/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 11:14:50 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 11:27:39 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_parse_env1(t_token *cmd, t_m *mini, int *size, int i)
{
	cmd = ft_remove_cmd(cmd, (*size)--, i);
	cmd = ft_parse_env(cmd, mini, (*size));
	return (cmd);
}

t_token	*ft_parse_env2(t_token *cmd, t_m *mini, int *size, int i)
{
	int		h;
	int		count;
	t_token	token;

	h = 0;
	count = 1;
	while (cmd[i].value[h])
	{
		token = ft_getarg(cmd[i].value, &h, mini);
		token.type = cmd[i].type;
		token.env = 0;
		cmd = ft_insert_cmd(cmd, ++(*size), i + count++, token);
		while (cmd[i].value[h] && ft_whitespace(cmd[i].value[h]))
			h++;
	}
	cmd = ft_remove_cmd(cmd, (*size)--, i);
	cmd = ft_parse_env(cmd, mini, (*size));
	return (cmd);
}

t_token	*ft_parse_env(t_token *cmd, t_m *mini, int size)
{
	int		i;

	i = 0;
	while (cmd[i].type)
	{
		if (cmd[i].env)
		{
			cmd[i].value = ft_quote_env(cmd[i].value, '"', mini);
			if (!cmd[i].value || ft_strlen(cmd[i].value) <= 0)
			{
				cmd = ft_parse_env1(cmd, mini, &size, i);
				break ;
			}
			cmd = ft_parse_env2(cmd, mini, &size, i);
			break ;
		}
		i++;
	}
	return (cmd);
}
