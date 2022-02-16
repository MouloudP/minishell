/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:44:03 by ahamdoun          #+#    #+#             */
/*   Updated: 2021/09/14 18:44:06 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	check_base(char *base)
{
	int		i;
	int		j;

	i = 0;
	if (base == NULL)
		return (0);
	while (base[i])
	{
		j = 0;
		while (base[j])
		{
			if (base[j] == base[i] && i != j)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_putnbr_base(long unsigned int nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr * -1 - 1 == 2147483647 || !(check_base(base)))
		return (0);
	if (nbr / ft_strlen(base) > 0)
		count = (ft_putnbr_base(nbr / ft_strlen(base), base) + 1);
	if (nbr >= 1)
		ft_putchar(base[nbr % ft_strlen(base)]);
	return (count);
}

int	ft_putnbr_base2(int nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr * -1 - 1 == 2147483647 || !(check_base(base)))
		return (0);
	if (nbr < 0)
	{
		nbr = nbr * -1;
		count = count + ft_putchar('-');
	}
	if (nbr / ft_strlen(base) > 0)
		count = count + ft_putnbr_base2(nbr / ft_strlen(base), base);
	if (nbr > 0)
		count = count + ft_putchar(base[nbr % ft_strlen(base)]);
	return (count);
}
