/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 13:15:24 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 18:36:56 by ahamdoun         ###   ########.fr       */
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
		rl_redisplay();
	}
}

void	cancel_c2(int sig)
{
	(void) sig;
}

void	cancel_delimiters(t_m *mini, int i)
{
	static t_m	*m;

	if (!m)
		m = mini;
	if (i >= 2)
	{
		m->exit_status = 128 + i;
		m->signal_save(i);
	}
	else
		m->canceldelimiters = i;
}

void	cancel_c3(int sig)
{
	if (sig == SIGINT)
	{
		cancel_delimiters(NULL, 1);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
	}
}

void	cancel_c4(int sig)
{
	(void) sig;
	write(1, "\n", 1);
}
