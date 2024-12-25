#include "minishell.h"

/*	EXECUTE_SIMPLE_CMD DEBUG
void execute_simple_cmd(t_cmd *cmd) {
    pid_t pid = fork();

	if (cmd->in)
	{
    	printf("Redirection input: %s\n", cmd->in->file);
    	if (cmd->in->fd < 0)
        	printf("Invalid file descriptor for input redirection\n");
	}	
	if (cmd->out) 
	{
    	printf("Redirection output: %s\n", cmd->out->file);
    	if (cmd->out->fd < 0)
        	printf("Invalid file descriptor for output redirection\n");
	}
    if (pid == 0) {
        if (cmd->in) {
            if (dup2(cmd->in->fd, STDIN_FILENO) < 0) { perror("dup2 input failed"); exit(1); }
            close(cmd->in->fd);  // Ferme après redirection
        }
        if (cmd->out) {
            if (dup2(cmd->out->fd, STDOUT_FILENO) < 0) { perror("dup2 output failed"); exit(1); }
            close(cmd->out->fd);  // Ferme après redirection
        }
        execvp(cmd->cmd[0], cmd->cmd);
        perror("execvp failed");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("fork failed");
    }
}
*/

void execute_simple_cmd(t_cmd *cmd) 
{
    pid_t pid ;
	
	pid = fork();
	if (pid < 0)
		exit(1);
    if (pid == 0) 
	{
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
        execvp(cmd->cmd[0], cmd->cmd);
        exit(1);
    }
	else if (pid > 0) 
        wait(NULL);
	write(1, "\n", 1);
}

void execute_multiple_cmds(t_cmd **cmds, int cmd_count)
{
    int i;

    // Traiter chaque commande
    for (i = 0; i < cmd_count; i++) 
    {
        // Exécution de la commande courante avec les redirections déjà définies
        execute_simple_cmd(cmds[i]);
    }
}

/*
static void	execute_command(t_cmd *cmd, int fds[], int i)
{
	int	j;

	if (i == 0)
		dup2(pipex.fd_input, 0);
	else
		dup2(fds[(i - 1) * 2], 0);
	if (i == pipex.cmdc - 1)
		dup2(pipex.fd_output, 1);
	else
		dup2(fds[i * 2 + 1], 1);
	j = -1;
	while (++j < 2 * (pipex.cmdc - 1))
		close(fds[j]);
	if (execve(pipex.cmds[i][0], pipex.cmds[i], pipex.path) == -1)
		exit_pipex(&pipex, NULL, EXIT_FAILURE);
}

t_status	process(t_cmd *cmd, char **env)
{
	int		*fds;
	pid_t	pid;
	int		i;
	t_cmd	*head;

	head = cmd;
	fds = malloc(sizeof(int) * 2 * (cmd_count(cmd) - 1));
	if (!fds)
		exit(1);
	pipe_cmd(fds, cmd);
	i = -1;
	while (++i < cmd_count(cmd))
	{
		pid = fork();
		if (pid < 0)
			return (FAILED);
		if (pid == 0)
			execute_command(cmd, fds, i);
	}
	ft_close_pipes(fds, cmd);
	ft_free(1, &fds);
	i = -1;
	while (++i < cmd_count(cmd))
		wait(NULL);
}
*/
/*
t_status	parsing(t_token *tokens)
{
	t_token	*current;
	t_cmd	*cmd;

	current = tokens;
	while (current)
	{
		cmd = parse_cmd(&current);
		if (cmd)
		{
			if (current && current->type == TOKEN_PIPE)
			{
				pipe(pipefd);
				execute_cmd(cmd, prev_pipefd, pipefd);
				close(pipefd[1]);
			}
			execute_cmd(cmd);
			free_cmd(cmd);
		}
		if (current && current->type == TOKEN_PIPE)
	}
	if (tokens->type = TOKEN_PIPE)
	{
		while (tokens)
		{
			if (is_redir(tokens))
				new = add_redir(tokens);
			tokens = tokens->next;
		}
	}
}


t_redir	*add_redir(t_token *tokens)
{
	t_redir	*current;
	t_redir	*redir_lst;
	t_redir	*new;
	t_redir	*prev;

	current = tokens;
	redir_lst = prev = NULL;
	while (current)
	{
		if (is_redir(current))
		{
			new = init_redir(current);
			if (!new)
				return (lst_free(redir_lst), NULL);
			if (!redir_lst)
				redir_lst = new;
			else
				prev->next = new;
			prev = new;
			current = del_redir_tokens(&tokens);
		}
		else
			current = current->next;
	}
	return (redir_lst);
}
*/