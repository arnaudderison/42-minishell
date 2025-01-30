/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parse_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:08:12 by aderison          #+#    #+#             */
/*   Updated: 2025/01/30 23:21:43 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_parse_error(char *value)
{
	ft_printf_fd(STDERR_FILENO,
		RED "minish: " YELLOW "syntax error " RESET "near unexpected token \
		\'%s\'\n", value);
}
