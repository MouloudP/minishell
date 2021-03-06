/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:50:32 by ahamdoun          #+#    #+#             */
/*   Updated: 2021/09/14 18:50:35 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_p(long unsigned int p)
{
	write(1, "0", 1);
	write(1, "x", 1);
	if (p == 0)
	{
		write(1, "0", 1);
		return (3);
	}
	return (ft_putnbr_base(p, "0123456789abcdef") + 3);
}
