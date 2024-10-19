/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_putnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:10:49 by aderison          #+#    #+#             */
/*   Updated: 2024/04/13 12:39:39 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	u_nbr_len(unsigned int nb)
{
	int	len;

	len = 1;
	while (nb > 9)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

int	ft_u_putnbr_fd(unsigned int nb, int fd)
{
	int	len;

	len = u_nbr_len(nb);
	if (nb > 9)
	{
		if (ft_u_putnbr_fd(nb / 10, fd) < 0)
			return (-1);
	}
	if (ft_putchar_fd(nb % 10 + '0', fd) < 0)
		return (-1);
	return (len);
}
