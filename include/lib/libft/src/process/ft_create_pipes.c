/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:18:01 by aderison          #+#    #+#             */
/*   Updated: 2024/05/11 23:20:48 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_create_pipes(int fds[], int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (pipe(fds + i * 2) < 0)
			return (-1);
		i++;
	}
	return (0);
}
