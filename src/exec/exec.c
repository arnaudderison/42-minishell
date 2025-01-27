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
			free(pipes[i]);
		}
	}
	// Libérer la mémoire principale du tableau de pipes
	free(pipes);
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

static int	execute_simple_cmd(t_cmd *cmd)
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
		if (cmd->in)
		{
			if (dup2(cmd->in->fd, STDIN_FILENO) < 0)
				exit(1);
			close(cmd->in->fd);
		}
		if (cmd->out)
		{
			printf("		cmd out\n");
			if (dup2(cmd->out->fd, STDOUT_FILENO) < 0)
				exit(1);
			close(cmd->out->fd);
		}
		execvp(cmd->cmd[0], cmd->cmd);
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
		if (WIFEXITED(status))
			cmd->exit_code = status;
		else
			cmd->exit_code = 1;
	}
	write(1, "\n", 1);
	setup_prompt_signals();
	return (cmd->exit_code);
}

// static void execute_child(t_cmd **cmds, int **pipes, int i, int cmd_count)
// {
//     int j;

//     // Rediriger l'entrée
//     if (cmds[i]->in && cmds[i]->in->fd >= 0) {
//         if (dup2(cmds[i]->in->fd, STDIN_FILENO) < 0)
//             exit(1);
//     }

//     // Rediriger la sortie
//     if (cmds[i]->out && cmds[i]->out->fd >= 0) {
//         if (dup2(cmds[i]->out->fd, STDOUT_FILENO) < 0)
//             exit(1);
//     }

//     // Fermer tous les pipes inutilisés
//     for (j = 0; j < cmd_count; j++) {
// 		if (j != i)
//         	close(pipes[j][0]);
//         if (j != i + 1)
// 			close(pipes[j][1]);
//     }

// 	execvp(cmds[i]->cmd[0], cmds[i]->cmd);
//     perror("execvp failed");
//     exit(1);
// }
static void	execute_child(t_cmd **cmds, int **pipes, int i, int cmd_count)
{
	int	j;

	if (cmds[i]->in)
	{	
		if (cmds[i]->in->fd >= 0)
			if (dup2(cmds[i]->in->fd, STDIN_FILENO) < 0)
				exit(1);
	}
	if (cmds[i]->out && cmds[i]->out->fd >= 0)
	{
		if (dup2(cmds[i]->out->fd, STDOUT_FILENO) < 0)
			exit(1);
	}
	for (j = 0; j < cmd_count; j++)
	{
		// if (j != i)
		close(pipes[j][0]);
		// if (j != i + 1)
		close(pipes[j][1]);
	}
	execvp(cmds[i]->cmd[0], cmds[i]->cmd);
	perror("execvp failed");
	exit(1);
}

static int	execute_multiple_cmds(t_cmd **cmds, int cmd_count)
{
	int	i;
	int	*pids;
	int	**pipes;
	int	status;

	// Allocation pipes and PIDs
	pipes = pipe_cmds(cmds);
	if (!pipes)
		return (write(1, "Error creating pipes\n", 22), 1);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		return (write(1, "Error allocating PIDs\n", 23), 1);
	// creation des processus enfants
	for (i = 0; i < cmd_count; i++)
	{
		if (cmds[i]->exit_code == 1)
			continue ;
		pids[i] = fork();
		if (pids[i] == -1)
			return (write(1, "Error with creating process\n", 28), 1);
		signal(SIGINT, handle_sigint_parent);
		// executer le processus enfant
		if (pids[i] == 0)
		{
			signal(SIGINT, handle_sigint_child);
			execute_child(cmds, pipes, i, cmd_count);
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
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			cmds[i]->exit_code = status;
		else
			cmds[i]->exit_code = 1;
	}
	free(pids);
	free_pipes(pipes, cmd_count);
	return (cmds[--i]->exit_code);
}

int	execute_cmds(t_cmd **cmds)
{
	int	n_cmds;
	int	exit_code;

	exit_code = 0;
	n_cmds = cmds_count(cmds);
	if (n_cmds == 0 || cmds[0]->exit_code > 0)
		return (-1);
	else if (n_cmds == 1)
		exit_code = execute_simple_cmd(cmds[0]);
	else
		exit_code = execute_multiple_cmds(cmds, n_cmds);
	return (exit_code);
}

int	handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

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
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (1);
}
