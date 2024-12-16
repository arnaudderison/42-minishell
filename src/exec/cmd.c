// #include "minishell.h"

// void	free_cmd(t_cmd *cmd)
// {
// 	if (cmd->in)
// 	{
// 		free(cmd->in->file);
// 		free(cmd->in);
// 	}
// 	if (cmd->out)
// 	{
// 		free(cmd->out->file);
// 		free(cmd->out);
// 	}
// 	if (cmd->append)
// 	{
// 		free(cmd->append->file);
// 		free(cmd->append);
// 	}
// 	if (cmd->heredoc)
// 	{
// 		free(cmd->heredoc->file);
// 		free(cmd->heredoc);
// 	}
// 	free(cmd);
// }

// int	pipe_count(t_token *token_lst)
// {
// 	int	count;

// 	count = 0;
// 	if (!token_lst)
// 		return (0);
// 	while (token_lst)
// 	{
// 		if (token_lst->type == TOKEN_PIPE)
// 			++count;
// 		token_lst = token_lst->next;
// 	}
// 	return (count);
// }

// t_status	access_cmd(t_cmd **cmd_tab)
// {
// 	int	i;

// 	i = -1;
// 	while (cmd_tab[++i]->cmd)
// 	{
// 		if (!access(cmd_tab[i]->cmd[0], X_OK) == 0)
// 			return (FAILED);
// 	}
// 	return (SUCCESS);
// }

// int	cmd_args_count(t_token *token_lst)
// {
// 	int	count;

// 	count = 0;
// 	if (!token_lst)
// 		return (0);
// 	while (token_lst && token_lst->type != TOKEN_PIPE)
// 	{
// 		if (token_lst->type == TOKEN_WORD)
// 			++count;
// 		token_lst = token_lst->next;
// 	}
// 	return (count);
// }

// /*  INIT_CMDS

// 	IN = nombre total de commandes (cmd_count)

// 	OUT = tableau de pointeurs vers des structures t_cmd initialisées,
// 		ou NULL si échec

// 	1. Alloue un tableau de pointeurs de taille cmd_count + 1.
// 	2. Pour chaque commande :
// 		- Alloue une structure t_cmd.
// 		- Initialise tous ses champs (cmd, in, out, heredoc, append,
// 			next) à NULL.
// 	3. Le dernier pointeur du tableau est NULL pour marquer la fin.
// */
// t_cmd	**init_cmds(int cmd_count)
// {
// 	t_cmd	**new_cmd;
// 	int		i;

// 	new_cmd = malloc(sizeof(t_cmd *) * (cmd_count + 1));
// 	if (!new_cmd)
// 		return (NULL);
// 	i = -1;
// 	while (++i < cmd_count)
// 	{
// 		new_cmd[i] = malloc(sizeof(t_cmd));
// 		if (!new_cmd[i])
// 			exit(1); // free
// 		new_cmd[i]->cmd = NULL;
// 		new_cmd[i]->in = NULL;
// 		new_cmd[i]->out = NULL;
// 		new_cmd[i]->heredoc = NULL;
// 		new_cmd[i]->append = NULL;
// 		new_cmd[i]->next = NULL;
// 	}
// 	new_cmd[i] = NULL;
// 	return (new_cmd);
// }

// t_token	*find_cmd(t_cmd *cmd, t_token *token_lst)
// {
// 	int	j;

// 	cmd->cmd = malloc(sizeof(char *) * (cmd_args_count(token_lst)) + 1);
// 	if (!cmd->cmd)
// 		exit(1); // free
// 	j = 0;
// 	while (token_lst->type != TOKEN_EOF && token_lst->type != TOKEN_PIPE)
// 	{
// 		if (token_lst->type == TOKEN_WORD)
// 		{
// 			cmd->cmd[j] = strdup(token_lst->value);
// 			if (!cmd->cmd[j++])
// 				exit(1); // free if error
// 		}
// 		token_lst = token_lst->next;
// 	} // PIPE || EOF
// 	cmd->cmd[j] = NULL;
// 	if (token_lst->type == TOKEN_PIPE)
// 		token_lst = token_lst->next;
// 	else if ((token_lst->type == TOKEN_EOF))
// 		return (NULL);
// 	return (token_lst);
// }

// t_status	set_cmd(t_cmd **cmd_tab, t_token *token_lst)
// {
// 	int		i;
// 	char	**cmd_arg;

// 	if (!cmd_tab || !token_lst)
// 		return (FAILED);
// 	i = 0;
// 	while (token_lst)
// 	{
// 		token_lst = find_cmd(cmd_tab[i], token_lst);
// 		if (!token_lst && i == 0)
// 			return (FAILED);
// 		++i;
// 	}
// 	cmd_tab[i] = NULL;
// 	return (SUCCESS);
// }

// /*  SET_REDIR

// 	IN = liste de t_token

// 	OUT = SUCCESS si

// 	1. alloue le tableau de s_cmd
// 	2. assigne les redirections des t_cmd
// 		modifie le type des tokens redirections et de leurs fichiers
// 	3. assigne le tableau de commande de chaque s_cmd
// */
// t_token		*set_redir(t_cmd **cmd, t_token *current);

// t_status	tokens_to_cmd(t_token *token_lst)
// {
// 	t_cmd	**cmd_tab;

// 	if (!(token_lst))
// 		return (FAILED);
// 	// allocate cmd
// 	cmd_tab = init_cmds(pipe_count(token_lst) + 1);
// 	token_lst = set_redir(cmd_tab, token_lst);
// 	if (set_cmd(cmd_tab, token_lst))
// 		exit(1);
// 	if (access_cmd(cmd_tab))
// 		return (FAILED); // free
// }
