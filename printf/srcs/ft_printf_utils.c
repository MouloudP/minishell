/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:43:03 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/03 20:18:26 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_fd2(char *s, int fd)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	ft_putnbr(int nb)
{
	if (nb == -2147483648)
		return (ft_putstr_fd2("-2147483648", 1));
	if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	return (ft_putnbr_base2(nb, "0123456789"));
}
