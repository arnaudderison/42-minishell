/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:14:02 by aderison          #+#    #+#             */
/*   Updated: 2024/05/11 23:19:44 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_close_pipes(int *fds, int count)
{
	int	i;

	i = 0;
	while (i < 2 * (count - 1))
	{
		close(fds[i]);
		i++;
	}
}
