/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execb.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:31:12 by aderison          #+#    #+#             */
/*   Updated: 2024/12/11 17:06:47 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this function will execute the builtins
t_status	execb(char **cmd, t_shell *shell)
{
	(void)shell;
	if (ft_strcmp(cmd[0], "echo") == 0 && ft_strlen(cmd[0]) == 4
		&& is_endl_echo(cmd[1]))
		return (echo(cmd + 2, false));
	if (ft_strcmp(cmd[0], "echo") == 0 && ft_strlen(cmd[0]) == 4)
		return (echo(cmd + 1, true));
	if (ft_strcmp(cmd[0], "cd") == 0 && ft_strlen(cmd[0]) == 2)
		return (cd(cmd[1]));
	if (ft_strcmp(cmd[0], "unset") == 0 && ft_strlen(cmd[0]) == 5)
		return (unset(shell, cmd + 1));
	return (FAILED);
}
