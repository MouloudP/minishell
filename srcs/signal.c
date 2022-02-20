/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pleveque <pleveque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:15:24 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/20 11:34:40 by pleveque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cancel_c(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		//rl_replace_line("\n\e[0;35mLeShell\e[0;33mDeLaHonte $>\e[0;37m ", 1);
		rl_redisplay();
	}
}

void	setup_signal(t_m *mini)
{
	mini->end = -1;
	mini->signal_save = signal(SIGINT, cancel_c);
}
