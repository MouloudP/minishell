/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:50:45 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/03 20:18:26 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_treat(char c, va_list arg)
{
	int	count;

	count = 0;
	if (c == 'i' || c == 'd')
		count = ft_putnbr(va_arg(arg, int));
	else if (c == 'c')
		count = ft_putchar(va_arg(arg, int));
	else if (c == 's')
		count = ft_putstr_fd2(va_arg(arg, char *), 1);
	else if (c == 'x')
		count = ft_x(va_arg(arg, unsigned int), 1);
	else if (c == 'X')
		count = ft_x(va_arg(arg, unsigned int), 0);
	else if (c == 'u')
		count = ft_u(va_arg(arg, unsigned int));
	else if (c == 'p')
		count = ft_p(va_arg(arg, long unsigned int));
	return (count);
}

int	ft_f(char c)
{
	char	*str;

	str = "cspdiuxX%";
	while (*str)
		if (*str++ == c)
			return (1);
	return (0);
}

int	ft_check_mix(const char *str, int i)
{
	int	count;
	int	find;

	count = 0;
	find = 0;
	if (str[i - 1] && str[i - 1] != '%')
		return (0);
	while (count <= i)
	{
		if (str[count] == '%')
		{
			if (str[count + 1] && ft_f(str[count + 1]))
			{
				count++;
				find = 1;
			}
			else
				find = 0;
		}
		else
			find = 0;
		count++;
	}
	return (find);
}

t_data	*ft_loop(const char *str, t_data *d, va_list arg)
{
	if (str[d->i] == '%')
	{
		if (str[d->i + 1] && (str[d->i + 1] == '%' || !(ft_f(str[d->i + 1]))))
		{
			ft_putchar(str[d->i + 1]);
			d->count++;
			d->i = d->i + 2;
		}
		else
			d->count = d->count + ft_treat(str[++d->i], arg);
	}
	else
	{
		if (ft_f(str[d->i]) && ft_check_mix(str, d->i))
			d->i++;
		else
		{
			ft_putchar(str[d->i++]);
			d->count++;
		}
	}
	return (d);
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	t_data	*data;
	int		count;

	count = 0;
	data = malloc(sizeof(t_data));
	data->i = 0;
	data->count = 0;
	va_start(arg, str);
	while (str[data->i])
	{
		data = ft_loop(str, data, arg);
	}
	va_end(arg);
	count = data->count;
	free(data);
	return (count);
}
