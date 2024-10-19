/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:13:30 by arnaud            #+#    #+#             */
/*   Updated: 2024/04/05 20:16:57 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	to_find_len;
	size_t	i;

	if (!str || !to_find)
		return (NULL);
	i = 0;
	to_find_len = ft_strlen(to_find);
	if (to_find_len == 0)
		return ((char *)str);
	if (len < to_find_len)
		return (NULL);
	while (str[i] && i <= len - to_find_len)
	{
		if (ft_strncmp(str + i, to_find, to_find_len) == 0)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
