/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:26:44 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/19 14:49:03 by ahamdoun         ###   ########.fr       */
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
    while (token[*i].type && token[*i].type != TOKEN_PIPE) // On va jusquau pipe
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

void	ft_create_pipe(t_token *token, int count)
{
	t_pipe	*pipe;
	int		i;

	pipe = malloc(sizeof(t_pipe) * (count + 1));
	i = 0;
	while (i < count)
	{
		pipe[i].cmd_count = 0;
		pipe[i].infile_count = 0;
		pipe[i].outfile_count = 0;
		if (token[i].type == TOKEN_ARGUMENT || token[i].type == TOKEN_COMMAND)
		{

		}
	}
}

void    ft_parse_token(t_token *token) // On va assigner les cmd
{
    int		i;
	int		count;
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