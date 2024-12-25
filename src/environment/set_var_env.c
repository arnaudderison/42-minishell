/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:06:42 by aderison          #+#    #+#             */
/*   Updated: 2024/12/25 14:41:19 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var_env(char *name, char *value, t_shell *shell)
{
	// if (!is_valid_identifier(name))
	// {
	// 	ft_printf_fd(STDERR_FILENO, "export: %s: not a valid identifier\n",
	// 		name);
	// 	return ;
	// }
	if (is_new_var(shell, name))
		add_var_env(ft_strdup(name), ft_strdup(value), &shell->user_env);
	if (get_env(name, &shell->envp) && !is_new_var(shell, name))
		edit_var_env(name, ft_strdup(value), &shell->envp);
	if (get_env(name, &shell->user_env) && !is_new_var(shell, name))
		edit_var_env(name, ft_strdup(value), &shell->user_env);
}
