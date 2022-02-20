/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 11:45:46 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/20 15:29:10 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_realloc_cmd(t_token	*cmd, int size)
{
    t_token	*new;
    int     i;

    new = malloc(sizeof(t_token) * (size + 2)); // Pour le nouveau et pour le NULL;
    i = 0;
    while (i < size)
    {
        new[i] = cmd[i];
        i++;
    }
    free(cmd);
    return (new);
}

t_token *ft_remove_cmd(t_token *cmd, int size, int del)
{
    t_token	*new;
    int     i;
    int     j;

    new = malloc(sizeof(t_token) * (size + 1));
    i = 0;
    j = 0;
    while (i < size)
    {
        if (i != del)
            new[j++] = cmd[i];
        i++;
    }
    free(cmd[del].value);
    free(cmd);
    return (new);
}

char    *ft_delimiters(char *s, t_token *token)
{
    char    *line;
    char    *ret;
    char    *temp;
    int     pipes[2];
    if (pipe(pipes) == -1)
    {
        perror("pipe");
        return (NULL);
    }
    
    ret = ft_calloc(sizeof(char), 1);
    line = ft_calloc(sizeof(char), 1);
    while (ft_strcmp(line, s) != 0)
    {
        free(line);
        line = readline("\e[0;35m>\e[0;37m ");
        temp = ret;
        ret = ft_strjoin(ret, "\n");
        free(temp);
        temp = ret;
        ret = ft_strjoin(ret, line);
        free(temp);
    }
    write(pipes[1], ret, ft_strlen(ret));
    close(pipes[1]);
    token->fd = pipes[1];
    token->value = ft_strdup(s);
    return (ret);
}