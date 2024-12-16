/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:29:50 by aderison          #+#    #+#             */
/*   Updated: 2024/12/07 00:31:46 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	export(char *var, t_shell shell)
{
	char	*value;

	value = ft_strchr(var, '=');
	if (value == NULL)
		return (FAILED);
	*value = '\0';
	value++;
	if (add_var_env(var, value, &(shell.envp)) != SUCCESS)
	{
		ft_printf_fd("Failed to set environment variable: %s\n", var,
			STDERR_FILENO);
		return (FAILED);
	}
	return (SUCCESS);
}
