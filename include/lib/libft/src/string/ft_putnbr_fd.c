/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:46:24 by arnaud            #+#    #+#             */
/*   Updated: 2024/04/13 12:06:26 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_int_len(int n)
{
	int				len;
	unsigned int	nb;

	len = 1;
	if (n < 0)
	{
		len++;
		nb = (unsigned int)(-n);
	}
	else
		nb = (unsigned int)(n);
	while (nb > 9)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

int	ft_putnbr_fd(int nb, int fd)
{
	int				len;
	unsigned int	num;

	len = ft_int_len(nb);
	if (nb < 0)
	{
		if (ft_putchar_fd('-', fd) < 0)
			return (-1);
		num = (unsigned int)(-nb);
	}
	else
		num = (unsigned int)(nb);
	if (num >= 10)
	{
		if (ft_putnbr_fd(num / 10, fd) < 0)
			return (-1);
	}
	if (ft_putchar_fd(num % 10 + '0', fd) < 0)
		return (-1);
	return (len);
}
