/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:03:35 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/23 13:22:11 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_fd(char *s, int fd)
{
	int	size;

	if (!s)
		return (-1);
	size = ft_strlen(s);
	write(fd, s, size);
	return (0);
}

int	input_error(char *error_type, char	*precision, int type)
{
	write_fd("\033[1;36m", 2);
	write_fd(error_type, 2);
	write_fd(": \033[1;31m", 2);
	if (type == -666)
	{
		perror("");
		write_fd("\033[0m", 2);
	}
	else
	{
		write_fd(precision, 2);
		write_fd("\033[0m\n", 2);
	}
	return (-1);
}
