/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 12:00:13 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/22 10:12:30 by pleveque         ###   ########.fr       */
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
	return (0);
}

int	ft_tern(int condition, int a, int b)
{
	if (condition == 1)
		return (a);
	return (b);
}

char	*ft_strdupp(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
