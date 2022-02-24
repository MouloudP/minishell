/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:01:54 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/24 19:33:28 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	long_atoi(const char *nptr)
{
	long long	i;
	long long	total;
	long long	neg;

	i = 0;
	total = 0;
	neg = 1;
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

/* check if the arg is a number */

int	check_argv(char *argv)
{
	int	j;

	if (!argv)
		return (1);
	if ((ft_strlen(argv) >= 20 && ft_strcmp(argv, "-9223372036854775808") > 0)
		|| (ft_strlen(argv) >= 19
			&& ft_strcmp(argv, "9223372036854775807") > 0))
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
	int	err;

	i = 1;
	err = 0;
	while (cmd[i])
		i++;
	if (i > 2 && ++err)
	{
		write(2, "exit: too many arguments\n", 25);
		if (check_argv(cmd[1]) == 0)
			return (1);
	}
	mini->print_exit = 1;
	mini->end = EXIT_SUCCESS;
	if (!cmd[1])
		return (0);
	if (check_argv(cmd[1]) == 0)
		return (long_atoi(cmd[1]));
	else
	{
		if (err == 0)
			write(2, "exit: numeric argument required\n", 32);
		return (mini->end = EXIT_FAILURE, 2);
	}
}
