/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:44:36 by ahamdoun          #+#    #+#             */
/*   Updated: 2021/09/14 18:45:09 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_x(unsigned int nb, int x)
{
	if (nb == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (x && nb > 0)
		return (ft_putnbr_base(nb, "0123456789abcdef") + 1);
	if (!(x) && nb > 0)
		return (ft_putnbr_base(nb, "0123456789ABCDEF") + 1);
	return (0);
}
