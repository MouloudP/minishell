/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:26:44 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/24 19:08:14 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_pipe(t_pipe *pipe, int count)
{
	int	i;
	int	j;

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
		ft_printf("\n\tFILES :\n\t\t");
		j = 0;
		while (j < pipe[i].files_count)
		{
			ft_printf("%s ", pipe[i].files[j].value);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	ft_parse_start(t_token *token, int *i)
{
	int	cmd;

	cmd = 1;
	while (token[*i].value && token[*i].type != TOKEN_PIPE)
	{
		if (token[*i].value && token[*i].type >= 4 && token[*i].type <= 8
			&& token[*i].type != TOKEN_REDIRECTION_DELIMTER)
		{
			(*i)++;
			if (token[*i].value && token[*i].type == TOKEN_ARGUMENT)
				token[*i].type = TOKEN_FILE;
		}
		else if (cmd && token[*i].value && token[*i].type == TOKEN_ARGUMENT)
		{
			token[*i].type = TOKEN_COMMAND;
			cmd = 0;
		}
		if (token[*i].value)
			(*i)++;
	}
}

t_token	ft_copy_token(t_token token)
{
	t_token	copy;

	copy.value = token.value;
	copy.type = token.type;
	copy.fd = token.fd;
	copy.env = token.env;
	return (copy);
}

void	ft_add_pipe(t_token *token, t_pipe *pipe, int i, int j)
{
	pipe[i].cmd = ft_malloc(sizeof(t_token) * (pipe[i].cmd_count + 2));
	pipe[i].files = ft_malloc(sizeof(t_token) * (pipe[i].files_count + 2));
	pipe[i].cmd_count = 0;
	pipe[i].files_count = 0;
	while (token[j].type && token[j].type != TOKEN_PIPE)
	{
		if (token[j].type == TOKEN_ARGUMENT || token[j].type == TOKEN_COMMAND)
		{
			pipe[i].cmd[pipe[i].cmd_count++] = ft_copy_token(token[j]);
		}
		else if (token[j].type >= TOKEN_REDIRECTION_INPUT
			&& token[j].type <= TOKEN_REDIRECTION_DELIMTER)
		{
			if (token[j].type != TOKEN_REDIRECTION_DELIMTER)
			{
				pipe[i].files[pipe[i].files_count] = ft_copy_token(token[++j]);
				pipe[i].files[pipe[i].files_count].type = token[j - 1].type;
			}
			else
				pipe[i].files[pipe[i].files_count] = ft_copy_token(token[j]);
			pipe[i].files_count++;
		}
		if (token[j].type)
			j++;
	}
}
