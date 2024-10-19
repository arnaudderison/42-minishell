/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:42:18 by arnaud            #+#    #+#             */
/*   Updated: 2024/04/05 20:06:03 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strdup(const char *str)
{
	int		str_len;
	char	*dup;
	int		i;

	if (!str)
		return (NULL);
	i = -1;
	str_len = ft_strlen(str);
	dup = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!dup)
		return (NULL);
	dup[str_len] = '\0';
	while (++i < str_len)
		dup[i] = str[i];
	return (dup);
}
