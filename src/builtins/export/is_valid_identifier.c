/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_identifier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:04:36 by aderison          #+#    #+#             */
/*   Updated: 2025/01/21 15:51:22 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		ft_printf_fd(2,
			RED "export: " RESET "%s: " YELLOW "not a valid identifier" RESET,
			str);
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_printf_fd(2,
				RED "export: " RESET "%s: " YELLOW "not a valid identifier" \
				RESET, str);
			return (0);
		}
		i++;
	}
	return (1);
}
