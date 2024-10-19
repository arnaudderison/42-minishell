/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 08:44:49 by arnaud            #+#    #+#             */
/*   Updated: 2024/04/05 20:37:28 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	j;
	size_t	len_src;
	size_t	i;
	int		total_len;
	size_t	len_dst;

	if (!dst || !src)
		return (0);
	j = 0;
	i = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (size > len_dst)
		total_len = len_dst + len_src;
	else
		total_len = len_src + size;
	j = len_dst;
	while (src[i] && j + 1 < size)
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = 0;
	return (total_len);
}
