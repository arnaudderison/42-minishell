
#include "minishell.h"

/*
FONCTION              RESPONSABILITE

clear_redir_token     Marque un token de redirection et son fichier associé comme inutilisables (type = NAO).
free_redir_cmd        Libère les ressources associées à une redirection dans une commande,
	en fonction de son type.
update_redir          Associe les descripteurs de fichiers ouverts à la commande selon le type de redirection.
open_redir_fd         Ouvre un fichier pour une redirection et retourne le descripteur de fichier (fd).
create_redir          Alloue et initialise une nouvelle structure de redirection avec le type et le fichier spécifié.
add_redir             Ajoute une redirection à une commande en libérant les anciennes redirections si nécessaire.
process_redir         Traite un token de redirection et l'associe à la commande correspondante.
set_redir             Gère les redirections et les pipes dans la liste de tokens et les assigne aux commandes.
*/

t_redir	*create_redir(int redir_type, char *file)
{
	t_redir	*new_redir;

	if (!file)
	{
		ft_printf("file = null\n");
		return (NULL);
	}
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = redir_type;
	new_redir->file = strdup(file);
	if (redir_type == TOKEN_REDIR_HEREDOC)
		new_redir->is_heredoc = 1;
	else
		new_redir->is_heredoc = 0;
	if (!new_redir->file)
		return (ft_free(1, &new_redir), NULL);
	if (redir_type != TOKEN_REDIR_HEREDOC)
	{
		new_redir->fd = open_redir_fd(*new_redir);
		if (new_redir->fd < 0)
			return (ft_free(2, &new_redir->file, &new_redir), NULL);
	}
	else
		new_redir->fd = -1;
			// comme c'est un heredoc le redir sera set plus tard
	return (new_redir);
}

// t_status	add_redir(t_cmd *cmd, int redir_type, char *file)
// {
// 	t_redir	*new_redir;

// 	if (!cmd || !file)
// 		return (PTR_NULL);
// 	new_redir = create_redir(redir_type, file);
// 	if (!new_redir)
//     {
//         cmd->exit_code = 1;
// 		return (FAILED);
//     }
// 	if (!update_redir(cmd, new_redir))
//     {
// 		ft_free(1, &new_redir);
//         return (FAILED);
//     }
// 	return (SUCCESS);
// }

t_status	add_redir(t_shell *sh, int redir_type, char *file, int i)
{
	t_redir	*new_redir;

	if (!sh->cmds[i] || !file)
		return (PTR_NULL);
	new_redir = create_redir(redir_type, file);
	if (!new_redir)
	{
		sh->cmds[i]->exit_code = 1;
		return (FAILED);
	}
	if (redir_type == TOKEN_REDIR_HEREDOC)
    {
		handle_heredoc(file);
        ft_free(1, &new_redir->file);
        new_redir->type = TOKEN_REDIR_IN;
        new_redir->fd = open("/tmp/heredoc_tmp", O_RDONLY);
        //new_redir->file = ft_strdup("/tmp/heredoc_tmp");
    }
	if (!update_redir(sh->cmds[i], new_redir))
	{
        ft_printf("Est ce que ca failed ?\n");
		free(new_redir);
		return (FAILED);
	}
	return (SUCCESS);
}

t_token	*process_redir(t_shell *sh, t_token *current, int i)
{
	t_token	*new_current;

	if (is_redir_op(current))
	{
		if (!add_redir(sh, current->type, current->next->value, i))
		{
			sh->cmds[i]->exit_code = 1;
			clear_redir_token(current);
			return (current->next->next);
		}
		clear_redir_token(current);
		new_current = current->next->next;
		if (!new_current)
			exit(1);
		current = new_current;
	}
	else
		current = current->next;
	return (current);
}

t_token	*set_redir(t_shell *sh, t_token *current)
{
	t_token	*head;
	int		i;

	if (!sh->cmds || !current)
		return (NULL);
	head = current;
	i = 0;
	while (current && current->type != TOKEN_EOF)
	{
		while (current && current->type != TOKEN_PIPE
			&& current->type != TOKEN_EOF)
		{
			current = process_redir(sh, current, i);
			if (!current)
				ft_printf("failed process_redir\n");
		}
		if (current && current->type == TOKEN_PIPE)
		{
			current = current->next;
			++i;
		}
	}
	return (head);
}
