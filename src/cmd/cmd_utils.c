#include "minishell.h"

/*	FONCTIONS

FONCTION                  RESPONSABILITÉ

free_cmd                 Libère la mémoire allouée pour une commande (t_cmd) et ses redirections associées.
free_cmd_array           Libère un tableau de commandes (t_cmd) et ses éléments, puis termine le programme avec un status.
pipe_count               Compte le nombre de pipes dans une liste de tokens.
cmd_args_count           Compte le nombre d'arguments dans une commande en fonction des tokens.
init_redir                Initialise les redirections (in, out, heredoc, append) d'une commande à NULL.
*/

void	free_cmd(t_cmd *cmd)
{
	printf("free cmd ---------------\n");
	if (cmd->in)
	{
		ft_free(1, cmd->in->file);
		ft_free(1, cmd->in);
	}
	if (cmd->out)
	{
		ft_free(1, cmd->out->file);
		ft_free(1, cmd->out);
	}
	if (cmd->append)
	{
		ft_free(1, cmd->append->file);
		ft_free(1, cmd->append);
	}
	if (cmd->heredoc)
	{
		ft_free(1, cmd->heredoc->file);
		ft_free(1, cmd->heredoc);
	}
	ft_free(1, cmd);
}

void	free_cmd_array(t_cmd **cmd_tab, int status)
{
    int i;

	printf("free cmd array------------\n");
    if (!cmd_tab)
		return ;
	i = -1;
    while (cmd_tab[++i])
	{
		printf("---------boucle free cmd array [%d]\n", i);
        free_cmd(cmd_tab[i]);
	}
    ft_free(1, cmd_tab);
	printf("END free cmd array------------\n");
	exit (status);
}

int		pipe_count(t_token *token_lst)
{
	int	count;

	count = 0;
	if (!token_lst)
		return (0);
	while (token_lst)
	{
		if (token_lst->type == TOKEN_PIPE)
			++count;
		token_lst = token_lst->next;
	}
	return (count);
}

int		cmd_args_count(t_token *token_lst)
{
	int	count;

	count = 0;
	if (!token_lst)
		return (0);
	while (token_lst && token_lst->type != TOKEN_PIPE)
	{
		if (token_lst->type == TOKEN_WORD)
			++count;
		token_lst = token_lst->next;
	}
	return (count);
}

void	display_cmds(t_cmd **cmd_tab)
{
    if (!cmd_tab) {
        printf("Command table is NULL\n");
        return;
    }

    for (int i = 0; cmd_tab[i]; i++) {
        printf("Command %d:\n", i);
        printf("  cmd: %p\n", (void *)cmd_tab[i]->cmd);
        printf("  in: %p\n", (void *)cmd_tab[i]->in);
        printf("  out: %p\n", (void *)cmd_tab[i]->out);
        printf("  heredoc: %p\n", (void *)cmd_tab[i]->heredoc);
        printf("  append: %p\n", (void *)cmd_tab[i]->append);
    }
}