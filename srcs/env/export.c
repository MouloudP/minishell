/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 09:51:42 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/27 17:37:07 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_copy_env(t_m *mini)
{
	t_env	*new;
	int		i;

	new = ft_malloc(sizeof(t_env) * (mini->env_lenght));
	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		new[i].name = mini->env[i].name;
		new[i].value = mini->env[i].value;
		new[i].init = mini->env[i].init;
		i++;
	}
	new[i].name = NULL;
	new[i].value = NULL;
	new[i].init = 0;
	return (new);
}

void	ft_copy_part(t_env *srcs, t_env *dest)
{
	srcs->name = dest->name;
	srcs->value = dest->value;
	srcs->init = dest->init;
}

void	ft_print_new_export(t_m *mini, int out_fd, t_env *new)
{
	int	i;

	i = 0;
	while (i < (mini->env_lenght - 1))
	{
		write(out_fd, "declare -x ", 11);
		if (new[i].init)
		{
			write(out_fd, new[i].name, ft_strlen(new[i].name));
			write(out_fd, "=\"", 2);
			write(out_fd, new[i].value, ft_strlen(new[i].value));
			write(out_fd, "\"\n", 2);
		}
		else
			write(out_fd, new[i].name, ft_strlen(new[i].name));
		i++;
	}
	free(new);
}

void	ft_printexport(t_m *mini, int out_fd)
{
	int		i;
	int		j;
	t_env	*new;
	t_env	temp;

	i = 0;
	new = ft_copy_env(mini);
	while (i < (mini->env_lenght - 1))
	{
		j = 0;
		while (j < (mini->env_lenght - 1))
		{
			if (new[j + 1].name && ft_strcmp(new[j].name, new[j + 1].name) > 0)
			{
				ft_copy_part(&temp, &new[j]);
				ft_copy_part(&new[j], &new[j + 1]);
				ft_copy_part(&new[j + 1], &temp);
			}
			j++;
		}
		i++;
	}
	ft_print_new_export(mini, out_fd, new);
}
