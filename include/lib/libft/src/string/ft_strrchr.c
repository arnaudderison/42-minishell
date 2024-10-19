/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:57:56 by arnaud            #+#    #+#             */
/*   Updated: 2024/04/05 20:10:28 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strrchr(const char *str, int charac)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)charac)
			return ((char *)(str + i));
		i--;
	}
	return (NULL);
}
