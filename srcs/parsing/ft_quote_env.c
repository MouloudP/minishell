/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:02:18 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/24 12:10:57 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_quote_env2(t_quote_env arg, char c, int i)
{
	if (ft_getenv(arg.mini, arg.temp))
		arg.copy = ft_strjoin(arg.temp2, ft_getenv(arg.mini, arg.temp));
	else
		arg.copy = ft_strdup(arg.temp2);
	free(arg.temp);
	free(arg.temp2);
	arg.temp = arg.copy;
	if (arg.str[i] == '}')
		arg.copy = ft_strjoin(arg.copy, arg.str + i + 1);
	else
		arg.copy = ft_strjoin(arg.copy, arg.str + i);
	free(arg.str);
	free(arg.temp);
	arg.str = arg.copy;
	arg.str = ft_quote_env(arg.str, c, arg.mini);
	return (arg.str);
}

void	ft_quote_env3(t_quote_env *arg, int start, int i)
{
	if (arg->str[i] == '}' && arg->str[start - 1] == '{')
	{
		arg->temp = ft_strndup(arg->temp, i - start);
		arg->temp2 = ft_strndup(arg->str, start - 2);
	}
	else
	{
		arg->temp = ft_strndup(arg->temp, i - start);
		arg->temp2 = ft_strndup(arg->str, start - 1);
	}
}

char	*ft_quote_env(char *str, char c, t_m *mini)
{
	int			i;
	int			start;
	t_quote_env	arg;

	i = -1;
	arg.mini = mini;
	while (str[++i] && c != '\'')
	{
		if (str[i] == '$')
		{
			start = i + 1;
			i++;
			if (str[i] == '{')
				start = (++i);
			while (str[i] && !ft_whitespace(str[i])
				&& str[i] != '$' && str[i] != '}')
				i++;
			arg.temp = str + start;
			arg.str = str;
			ft_quote_env3(&arg, start, i);
			str = ft_quote_env2(arg, c, i);
			break ;
		}
	}
	return (str);
}
