/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:40:51 by arnaud            #+#    #+#             */
/*   Updated: 2024/05/09 17:56:07 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
		return (write(fd, "(null)", ft_strlen("(null)")));
	return (write(fd, s, ft_strlen(s)));
}
