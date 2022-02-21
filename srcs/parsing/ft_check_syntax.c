/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:42:56 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/21 14:44:36 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_syntax(char *str)
{
	int i;
	int	*count;
	int error;

	i = 0;
	count = ft_calloc(sizeof(int), 255);
	error = 1;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else if (str[i] == '{')
			count[0]++;
		else if (str[i] == '}')
			count[1]++;
		else if (str[i] == '\'')
		{
			count[2]++;
			while (str[++i] && str[i] != '\'')
				i++;
			if (!str[i])
				error = 1;
			else
				count[2]++;
		}
		else if (str[i] == '\"')
		{
			count[3]++;
			while (str[++i] && str[i] != '\"' && str[i - 1] != '\\')
				i++;
			if (!str[i])
				error = 1;
			else
				count[3]++;
		}
		else if (str[i] == '|')
		{
			count[4]++;
			if (str[i + 1] == '|')
				error = 1;
			//while (str[++i])
		}
		i++
	}
	if (count[1] > count[0] || error)
		ft_printf("Minishell : parse error\n");
	free(count)
}

// 0 = {
// 1 = }
// 2 = '
// 3 = "
// 4 = |