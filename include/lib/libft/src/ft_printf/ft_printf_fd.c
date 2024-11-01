/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:28:24 by arnaud            #+#    #+#             */
/*   Updated: 2024/11/01 16:48:15 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	is_flag(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

static int	proc_command(va_list *args, char flag, int *len, int fd)
{
	int	tmp;

	tmp = 0;
	if (flag == 'c')
		tmp = ft_putchar_fd(va_arg(*args, int), fd);
	else if (flag == 's')
		tmp = ft_putstr_fd(va_arg(*args, char *), fd);
	else if (flag == 'p')
		tmp = ft_pointer(va_arg(*args, size_t), fd);
	else if (flag == 'd' || flag == 'i')
		tmp = ft_putnbr_fd(va_arg(*args, int), fd);
	else if (flag == 'u')
		tmp = ft_u_putnbr_fd(va_arg(*args, unsigned int), fd);
	else if (flag == 'x')
		tmp = ft_puthex_fd(va_arg(*args, int), 0, fd);
	else if (flag == 'X')
		tmp = ft_puthex_fd(va_arg(*args, int), 1, fd);
	else if (flag == '%')
		tmp = ft_putchar_fd('%', fd);
	if (tmp < 0)
		return (-1);
	else
		return (*len += tmp);
	return (*len);
}

static int	parse_strs(const char *strs, va_list *args, int *len_ptr, int fd)
{
	int	i;
	int	len;

	i = -1;
	len = *len_ptr;
	while (strs[++i])
	{
		if (strs[i] == '%' && is_flag(strs[i + 1]))
		{
			len = proc_command(args, strs[i + 1], &len, fd);
			if (len < 0)
				return (-1);
			i++;
		}
		else
		{
			len += ft_putchar_fd(strs[i], fd);
			if (len < 0)
				return (-1);
		}
	}
	*len_ptr = len;
	return (0);
}

int	ft_printf_fd(int fd, const char *strs, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, strs);
	if (parse_strs(strs, &args, &len, fd) < 0)
	{
		va_end(args);
		return (-1);
	}
	va_end(args);
	return (len);
}
