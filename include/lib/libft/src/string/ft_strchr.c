/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:08:08 by arnaud            #+#    #+#             */
/*   Updated: 2024/04/05 20:14:08 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strchr(const char *str, int charac)
{
	if (!str)
		return (0);
	while (*str || (char)charac == '\0')
	{
		if (*str == (char)charac)
			return ((char *)str);
		str++;
	}
	if (*str == charac)
		return ((char *)str);
	return (NULL);
}
