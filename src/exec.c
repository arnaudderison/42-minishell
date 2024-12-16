
# include "../../include/enum.h"
# include "../../include/structure.h"
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>

typedef struct s_redir {
    int     type;           // Type de redirection (<, >, >>, <<)
    char    *file;          // Nom du fichier
    int     fd;
} t_redir;

typedef struct s_cmd {
    int     type;
    char    **cmd;
    t_redir *in;
    t_redir *out;
    t_redir *heredoc;
    t_redir *append;
    struct t_cmd   *prev;
    struct t_cmd   *next;
}   t_cmd;

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

t_status process(t_cmd *cmd, char **env)
{
	int		*fds;
	pid_t	pid;
	int		i;
    t_cmd   *head = cmd;

	fds = malloc(sizeof(int) * 2 * (cmd_count(cmd) - 1));
	if (!fds)
		exit (1);
	pipe_cmd(fds, cmd);
	i = -1;
	while (++i < cmd_count(cmd))
	{
		pid = fork();
		if (pid < 0)
			return(FAILED);
		if (pid == 0)
			execute_command(cmd, fds, i);
	}
	ft_close_pipes(fds, *cmd);
	ft_free(1, &fds);
	i = -1;
	while (++i < cmd_count(cmd))
		wait(NULL);
}

/*
t_status parsing(t_token *tokens)
{
    t_token *current;
    t_cmd   *cmd;

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


t_redir *add_redir(t_token *tokens)
{
    t_redir *current;
    t_redir *redir_lst;
    t_redir *new;
    t_redir *prev;

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