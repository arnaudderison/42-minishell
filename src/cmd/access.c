/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:05:38 by plachard          #+#    #+#             */
/*   Updated: 2025/01/30 23:18:45 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**all_path(char *str_env)
{
	char	**env;
	char	*tmp;
	int		i;

	if (!str_env)
		return (NULL);
	env = ft_split(str_env, ':');
	if (!env)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		tmp = ft_strjoin(env[i], "/");
		if (!tmp)
		{
			while (i-- > 0)
				ft_free(1, &env[i]);
			ft_free(1, env);
			return (NULL);
		}
		ft_free(1, &env[i]);
		env[i] = tmp;
	}
	return (env);
}

static t_status	set_path(t_cmd *cmd, char **env)
{
	int	i;

	i = -1;
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
		return (FAILED);
	while (env && env[++i])
	{
		cmd->path = ft_strjoin(env[i], cmd->cmd[0]);
		if (!cmd->path)
			return (FAILED);
		if (access(cmd->path, X_OK) == 0)
			return (SUCCESS);
		ft_free(1, &cmd->path);
	}
	cmd->exit_code = 1;
	ft_printf(" command not found: %s\n", cmd->cmd[0]);
	return (FAILED);
}

static t_bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 && ft_strlen(cmd) == 4)
		return (1);
	if (ft_strcmp(cmd, "cd") == 0 && ft_strlen(cmd) == 2)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0 && ft_strlen(cmd) == 5)
		return (1);
	if (ft_strcmp(cmd, "export") == 0 && ft_strlen(cmd) == 6)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0 && ft_strlen(cmd) == 3)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0 && ft_strlen(cmd) == 4)
		return (1);
	if (ft_strcmp(cmd, "env") == 0 && ft_strlen(cmd) == 3)
		return (1);
	return (0);
}

static char	**set_env(t_shell *shell)
{
	char	*str_env;
	char	**env;

	str_env = get_path(shell);
	if (!str_env)
		exit(1);
	env = all_path(str_env);
	if (!env)
		exit(1);
	shell->env_execve = malloc(sizeof(char *) * 2);
	if (!shell->env_execve)
		exit(1);
	shell->env_execve[0] = ft_strdup(str_env);
	if (!shell->env_execve[0])
		exit(1);
	shell->env_execve[1] = NULL;
	return (env);
}

t_status	cmds_path(t_shell *shell)
{
	int		i;
	char	**env;

	env = set_env(shell);
	i = -1;
	while (shell->cmds[++i] && shell->cmds[i]->cmd)
	{
		if (is_builtin(shell->cmds[i]->cmd[0]))
			continue ;
		if (access(shell->cmds[i]->cmd[0], X_OK) == 0)
			shell->cmds[i]->path = ft_strdup(shell->cmds[i]->cmd[0]);
		else
		{
			if (!set_path(shell->cmds[i], env))
			{
				shell->cmds[i]->exit_code = 1;
				shell->cmds[i]->path = NULL;
			}
		}
	}
	ft_free_matrice(1, &env);
	return (SUCCESS);
}
