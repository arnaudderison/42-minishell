/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:46:52 by aderison          #+#    #+#             */
/*   Updated: 2024/05/10 22:39:55 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_free_matrice(unsigned int count, ...)
{
	va_list	args;
	void	***tab;
	int		i;

	va_start(args, count);
	while (count--)
	{
		tab = va_arg(args, void ***);
		if (*tab && **tab && tab)
		{
			i = 0;
			while ((*tab)[i])
			{
				free((*tab)[i]);
				(*tab)[i++] = NULL;
			}
			free(*tab);
			*tab = NULL;
		}
	}
	va_end(args);
}
