/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:02:04 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 19:26:47 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_times(int times, char *line, int fd_out)
{
	int	i;

	i = 0;
	while (i < times)
	{
		write(fd_out, line, 10);
		write(fd_out, "   ", 3);
		++i;
	}
	write(fd_out, "\n", 1);
	return (0);
}

int	ft_tree(char **cmd, int fd_out)
{
	char	lines[100] = " ======== ====**=======****=======**==== ========     ==        ==        ==       ====   ";
	int		i;
	int		size;

	(void)cmd;
	if (cmd[1] != NULL)
		size = ft_atoi(cmd[1]);
	else
		size = 1;
	i = 0;
	while (i < 10)
	{
		write_times(size, &lines[10 * i], fd_out);
		++i;
	}
	return (0);
}
