/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:01:54 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 16:42:25 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	long_atoi(const char *nptr)
{
	int			i;
	long long	total;
	int			neg;

	i = 0;
	total = 0;
	neg = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		total = total * 10 + (nptr[i] - '0');
		i++;
	}
	return (total * neg);
}

int	check_argv(char *argv)
{
	int	j;

	if ((ft_strlen(argv) <= 0) || (ft_strlen(argv) > 11)
		|| (long_atoi(argv) < -2147483648)
		|| (long_atoi(argv) > 2147483647))
		return (1);
	j = 0;
	while (argv[j])
	{
		if ((j == 0) && ((argv[j] > '9' || argv[j] < '0') && argv[j] != '-'))
			return (1);
		else if (j != 0 && (argv[j] > '9' || argv[j] < '0'))
			return (1);
		j++;
	}
	return (0);
}

int	ft_exit(char **cmd, t_m *mini)
{
	int	i;

	i = 1;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		mini->end = EXIT_FAILURE;
		write(2, "exit: too many arguments\n", 25);
	}
	else if (i == 1)
		mini->end = EXIT_SUCCESS;
	else if (check_argv(cmd[1]))
	{
		mini->end = EXIT_FAILURE;
		write(2, "exit: numeric argument required\n", 32);
	}
	else
		mini->end = (int) long_atoi(cmd[1]);
	return (1);
}
