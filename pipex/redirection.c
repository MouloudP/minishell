/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:45:20 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/22 10:09:08 by pleveque         ###   ########.fr       */
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

int	redirections(t_pipe pipe, int *input_fd, int *output_fd)
{
	int			i;

	i = -1;
	while (++i < pipe.infile_count)
	{
		if (*input_fd != 0)
			close(*input_fd);
		if (pipe.infile[i].type == TOKEN_REDIRECTION_OUTPUT)
			*input_fd = open(pipe.infile[i].value, O_RDONLY);
		if (pipe.infile[i].type == TOKEN_REDIRECTION_DELIMTER)
			*input_fd = pipe.infile[i].fd;
		if (*input_fd == -1)
			return (-1);
	}
	i = -1;
	while (++i < pipe.outfile_count)
	{
		if (*output_fd != 1)
			close(*output_fd);
		*output_fd = open_output(pipe.outfile[i].value,
				ft_tern(pipe.outfile[i].type == TOKEN_REDIRECTION_INPUT, 0, 1));
	}
	if (pipe.outfile_count > 0)
		return (1);
	return (0);
}
