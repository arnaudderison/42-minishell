/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:45:58 by aderison          #+#    #+#             */
/*   Updated: 2024/05/09 15:46:21 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_free(unsigned int count, ...)
{
	va_list	args;
	void	**tmp;

	va_start(args, count);
	while (count--)
	{
		tmp = va_arg(args, void **);
		if (*tmp)
		{
			free(*tmp);
			*tmp = NULL;
		}
	}
	va_end(args);
}
