/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:29:50 by aderison          #+#    #+#             */
/*   Updated: 2024/12/10 19:15:29 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	print_env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

// This fonction sorted the env name by alphabetical order.
static t_status	print_sorted_env(t_env *envp)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*start;
	t_env	tmp_swap;

	tmp = envp;
	start = envp;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
			{
				tmp_swap = *tmp;
				*tmp = *tmp2;
				*tmp2 = tmp_swap;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	print_env(start);
	return (SUCCESS);
}

// I must display the env variable if there is no argument.
t_status	export(char *var, t_shell shell)
{
	char	*value;

	value = ft_strchr(var, '=');
	if (value == NULL)
	{
		print_sorted_env(shell.envp);
		print_sorted_env(shell.user_env);
		return (SUCCESS);
	}
	*value = '\0';
	value++;
	if (add_var_env(var, value, &(shell.user_env)) != SUCCESS)
	{
		ft_printf_fd(STDERR_FILENO, "Failed to set environment variable: %s\n",
			var);
		return (FAILED);
	}
	return (SUCCESS);
}
