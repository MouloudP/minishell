/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamdoun <ahamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 18:39:59 by ahamdoun          #+#    #+#             */
/*   Updated: 2022/02/03 20:18:16 by ahamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_data
{
	int	count;
	int	i;
}	t_data;
int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putnbr(int n);
int		ft_putstr_fd2(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_putnbr_base(long unsigned int nbr, char *base);
int		ft_putnbr_base2(int nbr, char *base);
int		ft_x(unsigned int nb, int x);
int		ft_u(unsigned int nb);
int		ft_p(long unsigned int nb);

#endif
