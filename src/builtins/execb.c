/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:31:12 by aderison          #+#    #+#             */
/*   Updated: 2025/01/31 02:27:14 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function will execute the builtins
t_status	execb(char **cmd, t_shell *shell)
{
	if (ft_strcmp(cmd[0], "echo") == 0 && ft_strlen(cmd[0]) == 4)
		return (echo(cmd + 1, is_endl_echo(cmd + 1, 0)));
	if (ft_strcmp(cmd[0], "cd") == 0 && ft_strlen(cmd[0]) == 2)
		return (cd(cmd[1], shell));
	if (ft_strcmp(cmd[0], "unset") == 0 && ft_strlen(cmd[0]) == 5)
		return (unset(shell, cmd + 1));
	if (ft_strcmp(cmd[0], "export") == 0 && ft_strlen(cmd[0]) == 6)
		return (export(shell, cmd + 1));
	if (ft_strcmp(cmd[0], "pwd") == 0 && ft_strlen(cmd[0]) == 3)
		return (pwd(), SUCCESS);
	if (ft_strcmp(cmd[0], "exit") == 0 && ft_strlen(cmd[0]) == 4)
		return (exitb(cmd + 1, shell), SUCCESS);
	if (ft_strcmp(cmd[0], "env") == 0 && ft_strlen(cmd[0]) == 3)
	{
		env(shell->envp);
		env(shell->user_env);
		return (SUCCESS);
	}
	return (FAILED);
}
