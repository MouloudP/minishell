/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:45:20 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/19 12:30:21 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int reserved_arg(char *arg)
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

int	get_args(char **argv, t_str_tab **cmd_args, int *input_pipe, int *output_pipe)
{
	int			i;
	t_str_tab	*cmd_in_arg;
	int			redirection;

	redirection = 0;
	cmd_in_arg = NULL;
	cmd_in_arg = create_str_tab(cmd_in_arg, 30);
	i = 0;
	while (argv[i] && ft_strcmp(argv[i], "|") != 0)
	{
		if (ft_strcmp(argv[i], "<") == 0)
        {
			++i;
			*input_pipe = open(argv[i], O_RDONLY);
			redirection = 1;
		}
		else if (ft_strcmp(argv[i], ">") == 0)
        {
			++i;
			dup2(open_output(argv[i], 0), *output_pipe);
			redirection = 1;
		}
		else if (ft_strcmp(argv[i], ">>") == 0)
		{
			++i;
			dup2(open_output(argv[i], 1), *output_pipe);
			redirection = 1;
		}
		else
		{
			cmd_in_arg->str[cmd_in_arg->size] = argv[i];
			cmd_in_arg->size += 1;
		}
		++i;
	}
	cmd_in_arg->str[cmd_in_arg->size] = NULL;
	*cmd_args = cmd_in_arg;
	if (!argv[i] && redirection == 0)
	{
		close(*output_pipe);
		dup2(1, *output_pipe);
	}
	else if (argv[i] && ft_strcmp(argv[i], "|") == 0)
		++i;
	return (i);
}
