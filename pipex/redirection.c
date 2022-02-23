/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:45:20 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 16:56:05 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	reserved_arg(char *arg)
{
	if (!arg)
		return (-1);
	if (ft_strcmp(arg, ">") == 0)
		return (1);
	else if (ft_strcmp(arg, "<") == 0)
		return (1);
	else if (ft_strcmp(arg, "|") == 0)
		return (1);
	else if (ft_strcmp(arg, "<<") == 0)
		return (1);
	else if (ft_strcmp(arg, ">>") == 0)
		return (1);
	return (0);
}

t_str_tab	*create_str_tab(t_str_tab *tab, int size)
{
	tab = malloc(sizeof(t_str_tab));
	tab->size = 0;
	tab->str = malloc(sizeof(char *) * size);
	return (tab);
}

int	proceed_input(int *input_fd, t_token *file)
{
	if (*input_fd > 2)
		close(*input_fd);
	if (file->type == TOKEN_REDIRECTION_OUTPUT)
		*input_fd = open(file->value, O_RDONLY);
	else if (file->type == TOKEN_REDIRECTION_DELIMTER)
		*input_fd = file->fd;
	return (0);
}

int	proceed_output(int *output_fd, t_token *file)
{
	if (*output_fd != 1)
		close(*output_fd);
	*output_fd = open_output(file->value,
			ft_tern(file->type == TOKEN_REDIRECTION_INPUT, 0, 1));
	return (0);
}

int	redirections(t_pipe pipe, int *input_fd, int *output_fd)
{
	int			i;
	int			outfile_count;

	i = -1;
	outfile_count = 0;
	while (++i < pipe.files_count && pipe.files[i].value)
	{
		if (pipe.files[i].type == TOKEN_REDIRECTION_OUTPUT
			|| pipe.files[i].type == TOKEN_REDIRECTION_DELIMTER)
			proceed_input(input_fd, &pipe.files[i]);
		else
		{
			outfile_count = 1;
			proceed_output(output_fd, &pipe.files[i]);
		}
		if (*input_fd == INVALID_FD || *output_fd == INVALID_FD)
			return (input_error(pipe.files[i].value, NULL, -666), INVALID_FD);
	}
	if (outfile_count > 0)
		return (1);
	return (0);
}
