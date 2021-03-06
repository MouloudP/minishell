/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 18:25:28 by pleveque          #+#    #+#             */
/*   Updated: 2022/02/24 17:22:26 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_bis(t_m *mini)
{
	int	i;

	i = 0;
	while (mini->env_bis[i])
	{
		free(mini->env_bis[i]);
		i++;
	}
	free(mini->env_bis);
}

void	free_pipe(t_m *mini)
{
	int	i;

	i = 0;
	while (i < mini->pipe_lenght)
	{
		free(mini->pipe[i].cmd);
		free(mini->pipe[i].files);
		free(mini->pipe[i].parse_cmd);
		i++;
	}
	free(mini->pipe);
}

void	ft_exit_error(char *str, int num)
{
	write(2, str, ft_strlen(str));
	exit(num);
}

void	free_pwd(char *str, int fre)
{
	if (fre)
		free(str);
}

void	setup_signal(t_m *mini)
{
	mini->end = -1;
	mini->signal_save = signal(SIGINT, cancel_c);
	mini->cancel_c = cancel_c;
	mini->cancel_c2 = cancel_c2;
	mini->cancel_c4 = cancel_c4;
	signal(SIGQUIT, cancel_c2);
	cancel_delimiters(mini, 0);
}
