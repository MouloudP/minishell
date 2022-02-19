/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:00:13 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/18 12:31:03 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	fork_store(pid_t *pid_res)
{
	pid_t	pid;

	pid = fork();
	*pid_res = pid;
	if (pid == -1)
		return (-1);
	return (0);
}

int	open_store(int *fd_res, char *filename, int mode)
{
	*fd_res = open(filename, mode);
	if (*fd_res == -1)
		return (-1);
	return (0);
}

int	ft_strs_include(char *s, char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(s, str[i]) == 0)
			return (1);
	}
	return(0);
}
