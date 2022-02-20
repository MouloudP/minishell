/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:53:12 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/20 09:54:04 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_m *mini) // Pour le piero
{
	static int	first = 1;
	int			i;
	int			j;
	char		*temp;

	i = 0;
	j = 0;
	while (mini->env[i].name)
	{
		if (mini->env[i].init)
			j++;
		i++;
	}
	if (first == 0)
		free_env_bis(mini);
	first = 0;
	mini->env_bis = malloc(sizeof(char *) * (j + 1));
	i = 0;
	j = 0;
	while (mini->env[i].name)
	{
		if (mini->env[i].init)
		{
			temp = ft_strjoin(mini->env[i].name, "=");
			mini->env_bis[j++] = ft_strjoin(temp, mini->env[i].value);
			free(temp);
		}
		i++;
	}
	mini->env_bis[j++] = NULL;
}

void	ft_printenv(t_m *mini)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		if (mini->env[i].init)
			ft_printf("%s=%s\n", mini->env[i].name, mini->env[i].value);
		i++;
	}
}