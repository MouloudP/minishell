/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:45:20 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 13:16:50 by pleveque         ###   ########.fr       */
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
	int			outfile_count;

	i = -1;
	outfile_count = 0;
	while (++i < pipe.files_count && pipe.files[i].value)
	{
		if (pipe.files[i].type == TOKEN_REDIRECTION_OUTPUT || pipe.files[i].type == TOKEN_REDIRECTION_DELIMTER)
		{
			if (*input_fd > 2)
				close(*input_fd);
			if (pipe.files[i].type == TOKEN_REDIRECTION_OUTPUT)
				*input_fd = open(pipe.files[i].value, O_RDONLY);
			else if (pipe.files[i].type == TOKEN_REDIRECTION_DELIMTER)
				*input_fd = pipe.files[i].fd;
		}
		else
		{
			outfile_count = 1;
			if (*output_fd != 1)
				close(*output_fd);
			*output_fd = open_output(pipe.files[i].value,
					ft_tern(pipe.files[i].type == TOKEN_REDIRECTION_INPUT, 0, 1));
		}
		if (*input_fd == INVALID_FD || *output_fd == INVALID_FD)
			return (input_error(pipe.files[i].value, NULL, -666), INVALID_FD);
	}
	if (outfile_count > 0)
		return (1);
	return (0);
}
