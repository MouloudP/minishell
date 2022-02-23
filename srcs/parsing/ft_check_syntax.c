/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 16:42:56 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/23 16:55:04 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syntax1(char *str, int *count, int *i, int *error)
{
	count[2]++;
	while (str[(*i)] && str[(*i)] != '\'')
		(*i)++;
	if (!str[(*i)])
		*error = 1;
	else
		count[2]++;
}

void	ft_syntax2(char *str, int *count, int *i, int *error)
{
	count[3]++;
	while (str[(*i)] && str[(*i)] != '\"' && str[(*i) - 1] != '\\')
		(*i)++;
	if (!str[(*i)])
		*error = 1;
	else
		count[3]++;
}

void	ft_syntax3(char *str, int *count, int *i, int *error)
{
	count[4]++;
	while (str[(*i)] && ft_whitespace(str[(*i)]))
		(*i)++;
	if (str[(*i)] && str[(*i)] == '|')
		*error = 1;
}

void	ft_syntax4(char *str, int *count, int *i, int *error)
{
	if (str[*i] && str[*i] == '\\')
		(*i)++;
	else if (str[*i] && str[*i] == '{')
		count[0]++;
	else if (str[*i] && str[*i] == '}')
		count[1]++;
	else if (str[*i] && str[*i] == '\'' && ++(*i))
		ft_syntax1(str, count, i, error);
	else if (str[*i] && str[*i] == '\"' && ++(*i))
		ft_syntax2(str, count, i, error);
	else if (str[*i] && str[*i] == '|' && ++(*i))
		ft_syntax3(str, count, i, error);
	if (str[*i])
		(*i)++;
}

int	ft_check_syntax(char *str)
{
	int	i;
	int	*count;
	int	error;

	i = 0;
	count = ft_calloc(sizeof(int), 255);
	error = 0;
	while (str[i])
		ft_syntax4(str, count, &i, &error);
	if (error)
		write(2, "Minishell : syntax error\n", 25);
	free(count);
	return (error);
}

// 0 = {
// 1 = }
// 2 = '
// 3 = "
// 4 = |