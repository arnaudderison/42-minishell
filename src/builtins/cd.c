/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:32:50 by aderison          #+#    #+#             */
/*   Updated: 2024/12/25 14:48:45 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	cd(char *path, t_shell *sh)
{
	char *cwd;

	if (!path)
		path = get_env("HOME", &sh->envp);
	if (chdir(path) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "cd: %s: %s\n", path, strerror(errno));
		return (FAILED);
	}
	cwd =  getcwd(NULL, 0);
	if(!cwd)
		return (ft_printf_fd(2, "Error cwd"), UNKNOWN);
	set_var_env("PWD", cwd, sh);
	ft_free(1, &cwd);
	return (SUCCESS);
}
