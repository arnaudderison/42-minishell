/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:04:13 by plachard          #+#    #+#             */
/*   Updated: 2025/01/31 01:45:43 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	simple_cmd_child(t_cmd *cmd, t_shell *shell)
{
	restore_default_signals();
	signal(SIGQUIT, handle_sigquit);
	if (cmd->in)
	{
		if (dup2(cmd->in->fd, STDIN_FILENO) < 0)
			exit(1);
		close(cmd->in->fd);
	}
	if (cmd->out)
	{
		if (dup2(cmd->out->fd, STDOUT_FILENO) < 0)
			exit(1);
		close(cmd->out->fd);
	}
	execve(cmd->path, cmd->cmd, shell->env_execve);
	exit(1);
}

static void	simple_cmd_parent(t_cmd *cmd, pid_t pid, int status)
{
	setup_exec_signals();
	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		cmd->exit_code = status;
		exit(EXIT_FAILURE);
	}
	if (WIFSIGNALED(status))
		cmd->exit_code = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		cmd->exit_code = WEXITSTATUS(status);
	else
		cmd->exit_code = status;
}

static int	execute_simple_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		simple_cmd_child(cmd, shell);
	else if (pid > 0)
		simple_cmd_parent(cmd, pid, status);
	setup_prompt_signals();
	return (cmd->exit_code);
}

int	execute_cmds(t_shell *shell)
{
	int	n_cmds;
	int	exit_code;

	exit_code = 0;
	n_cmds = cmds_count(shell->cmds);
	if (n_cmds == 0 || n_cmds > 50)
		return (-1);
	if (shell->cmds[0]->exit_code > 0)
		return (-1);
	else if (n_cmds == 1)
	{
		if (!execb(shell->cmds[0]->cmd, shell))
			exit_code = execute_simple_cmd(shell->cmds[0], shell);
	}
	else
		exit_code = execute_multiple_cmds(shell, n_cmds);
	return (exit_code);
}
