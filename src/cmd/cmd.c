#include "minishell.h"

/*	FONCTIONS

FONCTION                  RESPONSABILITÉ

init_cmd                 Crée et initialise une nouvelle commande (t_cmd) avec des redirections vides.
init_cmd_array           Alloue un tableau de commandes (t_cmd) en fonction du nombre de commandes à traiter.
find_cmd                 Extrait les arguments d'une commande à partir de la liste de tokens et les assigne à la commande.
set_cmd                  Associe les commandes à un tableau en parcourant les tokens, et gère l'assignation des arguments.
tokens_to_cmd            Orchestrer la conversion des tokens en un tableau de commandes avec redirections et arguments.
*/

void 	init_redir(t_cmd *cmd)
{
    cmd->in = NULL;
    cmd->out = NULL;
	// cmd->append = NULL;
	cmd->heredoc = NULL;
}

t_cmd *init_cmd()
{
    t_cmd *new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
    new_cmd->cmd = NULL;
    init_redir(new_cmd);
    return (new_cmd);
}

t_cmd	**init_cmd_array(int cmd_count)
{
	t_cmd	**cmd_tab;
	int		i;

	cmd_tab = malloc(sizeof(t_cmd) * (cmd_count + 1));
	if (!cmd_tab)
		return (NULL);
	i = -1;
	while (++i < cmd_count)
	{
		cmd_tab[i] = init_cmd();
		if (!cmd_tab[i])
			free_cmd_array(cmd_tab, 1);
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

t_token	*find_cmd(t_cmd *cmd, t_token *token_lst)
{
	int	j;

	cmd->cmd = malloc(sizeof(char *) * (cmd_args_count(token_lst) + 1));
	if (!cmd->cmd)
		exit(1); // free
	j = 0;
	while (token_lst->type != TOKEN_EOF && token_lst->type != TOKEN_PIPE)
	{
		if (token_lst->type == TOKEN_WORD)
		{
			cmd->cmd[j] = strdup(token_lst->value);
			if (!cmd->cmd[j++])
				exit(1); // free if error
		}
		token_lst = token_lst->next;
	} // PIPE || EOF
	cmd->cmd[j] = NULL;
	if (token_lst->type == TOKEN_PIPE)
		token_lst = token_lst->next;
	else if ((token_lst->type == TOKEN_EOF))
		return (token_lst);
	return (token_lst);
}

t_status	set_cmd(t_cmd **cmd_tab, t_token *token_lst)
{
	int		i;

	if (!cmd_tab || !token_lst)
		return (FAILED);
	i = 0;
	while (token_lst->type != TOKEN_EOF)
	{
		token_lst = find_cmd(cmd_tab[i], token_lst);
		
		if (!token_lst && i == 0)
			return (FAILED);
		++i;
	}
	cmd_tab[i] = NULL;
	return (SUCCESS);
}

t_status tokens_to_cmd(t_shell *shell)
{
	t_token	*token_lst;

	token_lst = shell->tokens;
	if (!(token_lst))
		return (FAILED);
	shell->cmds = init_cmd_array(pipe_count(token_lst) + 1);
	if (!shell->cmds)
		return (FAILED);
	token_lst = set_redir(shell->cmds, token_lst);
	if (!set_cmd(shell->cmds, token_lst))
	{
		free_cmd_array(shell->cmds, -1);
		return (FAILED);
	}
	return (SUCCESS);
}
