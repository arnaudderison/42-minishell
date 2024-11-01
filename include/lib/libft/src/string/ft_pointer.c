/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:50:12 by aderison          #+#    #+#             */
/*   Updated: 2024/11/01 16:46:31 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	print_pointer(size_t adrr, char *base, int fd)
{
	char	string[17];
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (adrr != 0)
	{
		string[i++] = base[adrr % 16];
		adrr /= 16;
	}
	while (i--)
	{
		if (ft_putchar_fd(string[i], fd) < 0)
			return (-1);
		len += 1;
	}
	return (len);
}

int	ft_pointer(size_t addr, int fd)
{
	int	len;
	int	result;

	if (write(fd, "0x", 2) < 0)
		return (-1);
	len = 2;
	if (addr == 0)
	{
		if (write(fd, "0", 1) < 0)
			return (-1);
		len++;
	}
	else
	{
		result = print_pointer(addr, "0123456789abcdef", fd);
		if (result < 0)
			return (-1);
		len += result;
	}
	return (len);
}
