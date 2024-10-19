/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 21:23:28 by arnaud            #+#    #+#             */
/*   Updated: 2024/04/05 19:58:14 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_ptr;
	size_t				i;

	if (!s)
		return (NULL);
	i = -1;
	s_ptr = (unsigned char *)s;
	while (++i < n)
	{
		if (s_ptr[i] == (unsigned char)c)
			return ((void *)s + i);
	}
	return (NULL);
}
