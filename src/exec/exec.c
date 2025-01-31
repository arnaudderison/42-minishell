/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:04:13 by plachard          #+#    #+#             */
/*   Updated: 2025/01/31 01:00:00 by plachard         ###   ########.fr       */
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
		cmd->exit_code = WIFESTATUS(status);
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
		// ft_printf_fd(2, "PATH = %s  CMD = %s ENV = %s\n", cmd->path,
		// cmd->cmd[0], shell->env_execve[0]);
		execve(cmd->path, cmd->cmd, shell->env_execve);
		exit(1);
	}
	else if (pid > 0)
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
	setup_prompt_signals();
	return (cmd->exit_code);
}

static void	dup_io(t_shell *sh, int i)
{
	if (sh->cmds[i]->in)
	{
		if (sh->cmds[i]->in->fd >= 0)
			if (dup2(sh->cmds[i]->in->fd, STDIN_FILENO) < 0)
				exit(1);
	}
	if (sh->cmds[i]->out && sh->cmds[i]->out->fd >= 0)
	{
		if (dup2(sh->cmds[i]->out->fd, STDOUT_FILENO) < 0)
			exit(1);
	}
	return ;
}

static void	execute_child(t_shell *sh, int **pipes, int i, int cmd_count)
{
	int	j;

	dup_io(sh, i);
	j = -1;
	while (++j < cmd_count)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	if (execb(sh->cmds[i]->cmd, sh))
		exit(1);
	else
	{
		execve(sh->cmds[i]->path, sh->cmds[i]->cmd, sh->env_execve);
		perror("execvp failed");
		exit(1);
	}
}

static int	execute_multiple_cmds(t_shell *sh, int cmd_count)
{
	int	i;
	int	*pids;
	int	**pipes;
	int	status;

	// Allocation pipes and PIDs
	//	if (!(alloc_exec(&pipes, &pids)))
	// return (1);
	pipes = pipe_cmds(sh->cmds);
	if (!pipes)
		return (write(1, "Error creating pipes\n", 22), 1);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (write(1, "Error allocating PIDs\n", 23), 1);
		
	multi_cmd_child(sh, i, cmd_count)
	// creation des processus enfants
	for (i = 0; i < cmd_count; i++)
	{
		if (sh->cmds[i]->exit_code == 1)
			continue ;
		pids[i] = fork();
		if (pids[i] == -1)
			return (write(1, "Error with creating process\n", 28), 1);
		signal(SIGINT, handle_sigint_parent);
		// executer le processus enfant
		if (pids[i] == 0)
		{
			signal(SIGINT, handle_sigint_child);
			execute_child(sh, pipes, i, cmd_count);
			fprintf(stderr, "oupsidouille\n");
		}
	}
	// fermer fd dans le processus parent
	for (i = 0; i < cmd_count; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	// attendre enfants
	for (i = 0; i < cmd_count; i++)
	{
		if (sh->cmds[i]->exit_code == 1)
			continue ;
		status = 0;
		if (sh->cmds[i]->exit_code == 1)
			continue ;
		fprintf(stderr, "cmd[%d] = %s\n", i, sh->cmds[i]->cmd[0]);
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpidcaca");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			sh->cmds[i]->exit_code = status;
		else
			sh->cmds[i]->exit_code = 1;
	}
	ft_free(1, &pids);
	fprintf(stderr, "FREE PIPES %d\n", cmd_count);
	free_pipes(pipes, cmd_count);
	return (sh->cmds[--i]->exit_code);
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
