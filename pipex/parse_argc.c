/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:45:20 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/18 14:55:04 by pleveque         ###   ########.fr       */
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

t_stack	*outfiles_chevron(char **argv, t_stack *outfile_tmp, int *i, int mode)
{
	char	buffer[1023];
	int		ret;
	int		fd;
	char	*outfile;

	++*i;
	outfile = argv[*i];
	if (!outfile)
		return (input_error("parse error near '\\n'", NULL, 0), NULL);
	fd = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1)
		return (input_error("cant open fd", NULL, 0), NULL);
	close(fd);
	if (mode == 0)
		unlink(outfile);
	fd = open(outfile, O_RDWR | O_CREAT, S_IRWXU);
	if (fd == -1)
		return (input_error("cant open fd", NULL, 0), NULL);
	ret = 1023;
	while (ret == 1023)
		ret = read(fd, buffer, 1023);
	outfile_tmp->v[outfile_tmp->size] = fd;
	outfile_tmp->size += 1;
	return (outfile_tmp);
}

t_str_tab	*cmd_adding(char **argv, t_str_tab *cmd_in_arg, int *i, int *cmd_index)
{
	if (*cmd_index == -1)
		*cmd_index = *i;
	cmd_in_arg->str[cmd_in_arg->size] = argv[*i];
	cmd_in_arg->size += 1;
	return (cmd_in_arg);
}

t_str_tab	*create_str_tab(t_str_tab *tab, int size)
{
	tab = malloc(sizeof(t_str_tab));
	tab->size = 0;
	tab->str = malloc(sizeof(char *) * size);
	return (tab);
}

t_stack	*create_stack(t_stack *stack, int size)
{
	stack = malloc(sizeof(t_stack));
	stack->size = 0;
	stack->v = malloc(sizeof(int) * size);
	return (stack);
}

int	change_in_out(int first_pipe, char **argv, t_stack **outfiles, t_str_tab **cmd_args)
{
	int			cmd_index;
	int			i;
	t_str_tab	*cmd_in_arg;
	t_stack		*outfile_tmp;

	(void)first_pipe;
	outfile_tmp = NULL;
	cmd_in_arg = NULL;
	cmd_in_arg = create_str_tab(cmd_in_arg, 30);
	outfile_tmp = create_stack(outfile_tmp, 30);
	cmd_index = -1;
	i = 0;
	while (argv[i] && ft_strcmp(argv[i], "|") != 0)
	{
		if (ft_strcmp(argv[i], ">") == 0)
			outfile_tmp = outfiles_chevron(argv, outfile_tmp, &i, 0);
		else
			cmd_in_arg = cmd_adding(argv, cmd_in_arg, &i, &cmd_index);
		// else if (ft_strcmp(argv[i], "<") == 0)
		// 	infile_tmp = infile_chevron(argv, &outfile_tmp, &i);
		// else if (ft_strcmp(argv[i], "<<") == 0)
		// {
		// 	//the infile will be the newly created fd by the functiom strange_entry
		// 	strange_entry(fd);
		// 	infile_tmp = infile_chevron(argv, &outfile_tmp, &i);
		// }
		// else if (ft_strcmp(argv[i], ">>") == 0)
		// {
		// 	//the fd will delete the old file
		// 	infile_tmp = infile_chevron(argv, &outfile_tmp, &i);
		// }
		++i;
	}
	cmd_in_arg->str[cmd_in_arg->size] = NULL;
	*cmd_args = cmd_in_arg;
	*outfiles = outfile_tmp;
	if (argv[i] && ft_strcmp(argv[i], "|") == 0)
		++i;
	return (i);
}
