/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:03:19 by aderison          #+#    #+#             */
/*   Updated: 2024/10/19 22:10:17 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(t_error err, const char *file, int line)
{
	if (err == ERR_MALLOC)
		ft_printf(RED "MALLOC ERROR:" RESET "file : %s line: %d", file, line);
	if (err == ERR_NULL_PTR)
		ft_printf(RED "POINTER NULL:" RESET "file : %s line: %d", file, line);
}
