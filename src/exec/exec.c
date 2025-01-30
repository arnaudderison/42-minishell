#include "minishell.h"

void	free_pipes(int **pipes, int n_pipes)
{
	int	i;

	if (!pipes)
		return ;
	for (i = 0; i < n_pipes; i++)
	{
		if (pipes[i])
		{
			// Fermer les descripteurs de fichier associés au pipe
			close(pipes[i][0]);
			close(pipes[i][1]);
			// Libérer la mémoire du tableau pour ce pipe
			ft_free(1, &pipes[i]);
		}
	}
	// Libérer la mémoire principale du tableau de pipes
	free(pipes);
	pipes = NULL;
}

static int	cmds_count(t_cmd **cmds)
{
	int	count;

	count = 0;
	while (cmds[count])
		++count;
	return (count);
}

static void	set_pipes(t_cmd **cmds, int **pipes, int i)
{
	// attention ajout pas gerer in premiere commande
	if (!cmds[i]->in && i != 0)
	{
		cmds[i]->in = (t_redir *)malloc(sizeof(t_redir));
		if (!cmds[i]->in)
			exit(1);
		cmds[i]->in->fd = pipes[i][0];
		cmds[i]->in->file = NULL;
	}
	if (!cmds[i]->out)
	{
		cmds[i]->out = (t_redir *)malloc(sizeof(t_redir));
		if (!cmds[i]->out)
			exit(1);
		if (i == (cmds_count(cmds) - 1))
			cmds[i]->out->fd = 1;
		else
			cmds[i]->out->fd = pipes[i + 1][1];
		cmds[i]->out->file = NULL;
	}
	return ;
}

static int	**pipe_cmds(t_cmd **cmds)
{
	int	**pipes;
	int	i;
	int	n;

	// create pipes
	n = cmds_count(cmds);
	pipes = malloc(sizeof(int *) * (n + 1));
	i = -1;
	while (++i < n + 1) // ??? n ou n + 1
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			exit(1);
		if (pipe(pipes[i]) < 0)
			exit(1);
	}
	// set pipes
	i = -1;
	while (++i < n)
		set_pipes(cmds, pipes, i);
	// pipes[0][0] = STDIN_FILENO;
	// pipes[n+1][1] = STDOUT_FILENO;
	return (pipes);
}

static int	execute_simple_cmd(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;

	// ft_printf("%s\n", shell->env_execve[0]);
	status = 0;
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		restore_default_signals();
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
			exit(EXIT_FAILURE);
		}
		if (WIFSIGNALED(status))
			cmd->exit_code = 128 + WTERMSIG(status);
		else if (WIFEXITED(status))
			cmd->exit_code = status;
		else
			cmd->exit_code = status;
	}
	setup_prompt_signals();
	return (cmd->exit_code);
}

static void	execute_child(t_shell *sh, int **pipes, int i, int cmd_count)
{
	int	j;

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
	for (j = 0; j < cmd_count; j++)
	{
		// if (j != i)
		close(pipes[j][0]);
		// if (j != i + 1)
		close(pipes[j][1]);
	}
	fprintf(stderr, "EXEC CHILD = %s\n", sh->cmds[i]->cmd[0]);
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
	pipes = pipe_cmds(sh->cmds);
	if (!pipes)
		return (write(1, "Error creating pipes\n", 22), 1);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (write(1, "Error allocating PIDs\n", 23), 1);
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

int	handle_heredoc(char *delimiter, t_shell *sh)
{
	char	*line;
	int		fd;
	char	*expanded;

	expanded = NULL;
	restore_default_signals();
	fd = open("/tmp/heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		expanded = expand_input(line, sh);
		write(fd, expanded, strlen(expanded));
		write(fd, "\n", 1);
		free(line);
		ft_free(1, &expanded);
	}
	close(fd);
	return (1);
}
