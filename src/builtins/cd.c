/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:32:50 by aderison          #+#    #+#             */
/*   Updated: 2024/12/20 18:11:22 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	cd(char *path, t_shell *sh)
{
	if (!path)
		path = get_env("HOME", &sh->envp);
	if (chdir(path) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		return (FAILED);
	}
	set_var_env("PWD", getcwd(NULL, 0), sh);
	return (SUCCESS);
}
