/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multi_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 01:44:20 by plachard          #+#    #+#             */
/*   Updated: 2025/01/31 02:41:45 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_status	multi_cmd_child(t_shell *sh, pid_t *pids, int **pipes)
{
	int	i;
	int	cmd_count;

	i = -1;
	cmd_count = cmds_count(sh->cmds);
	while (++i < cmd_count)
	{
		if (sh->cmds[i]->exit_code == 1)
			continue ;
		pids[i] = fork();
		if (pids[i] == -1)
			return (write(1, "Error with creating process\n", 28), FAILED);
		signal(SIGINT, handle_sigint_parent);
		if (pids[i] == 0)
		{
			signal(SIGINT, handle_sigint_child);
			execute_child(sh, pipes, i, cmd_count);
		}
	}
	return (SUCCESS);
}

static void	wait_child(t_shell *sh, pid_t *pids, int cmd_count)
{
	int	i;
	int	status;

	i = -1;
	while (++i < cmd_count)
	{
		if (sh->cmds[i]->exit_code == 1)
			continue ;
		status = 0;
		if (sh->cmds[i]->exit_code == 1)
			continue ;
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
	return ;
}

int	execute_multiple_cmds(t_shell *sh, int cmd_count)
{
	pid_t	*pids;
	int		**pipes;

	pipes = pipe_cmds(sh->cmds);
	if (!pipes)
		return (write(1, "Error creating pipes\n", 22), 1);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (write(1, "Error allocating PIDs\n", 23), 1);
	if (!multi_cmd_child(sh, pids, pipes))
		return (1);
	close_pipes(pipes, cmd_count);
	wait_child(sh, pids, cmd_count);
	ft_free(1, &pids);
	free_pipes(pipes, cmd_count);
	return (sh->cmds[--cmd_count]->exit_code);
}
