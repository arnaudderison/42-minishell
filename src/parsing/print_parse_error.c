/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 15:08:12 by aderison          #+#    #+#             */
/*   Updated: 2024/11/02 15:10:10 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_parse_error(char *value)
{
    ft_printf_fd(
			STDERR_FILENO,
			RED "minish: " YELLOW "syntax error " \
			RESET "near unexpected token \'%s\'\n",
			value);
}
