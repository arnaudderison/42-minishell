
#include "minishell.h"

/*
FONCTION              RESPONSABILITE

clear_redir_token     Marque un token de redirection et son fichier associé comme inutilisables (type = NAO).
free_redir_cmd        Libère les ressources associées à une redirection dans une commande, en fonction de son type.
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
        ft_printf("                file = null\n");
		return (NULL);
    }
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return(NULL);
	new_redir->type = redir_type;
	new_redir->file = strdup(file);
	if (!new_redir->file)
		return(ft_free(1, &new_redir), NULL);
	new_redir->fd = open_redir_fd(*new_redir);
	if (new_redir->fd < 0)
		return(ft_free(2, &new_redir->file, &new_redir), NULL);
	return (new_redir);
}

t_status	add_redir(t_cmd *cmd, int redir_type, char *file)
{
	t_redir	*new_redir;

	if (!cmd || !file)
		return (PTR_NULL);
	new_redir = create_redir(redir_type, file);
	if (!new_redir)
    {
        cmd->exit_code = 1;  
		return (FAILED);
    }
	if (!update_redir(cmd, new_redir))
    {
		ft_free(1, &new_redir);
        return (FAILED);
    }
	return (SUCCESS);
}

t_token *process_redir(t_cmd *cmd, t_token *current)
{
    t_token *new_current;

    if (is_redir_op(current))
    {
        if (!add_redir(cmd, current->type, current->next->value))
        {
            cmd->exit_code = 1;
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
    return current;
}

t_token *set_redir(t_cmd **cmds, t_token *current)
{
    t_token *head;
    int i;

    if (!cmds || !current)
        return (NULL);
    head = current;
    i = 0;
    while (current && current->type != TOKEN_EOF)
    {
        while (current && current->type != TOKEN_PIPE && current->type != TOKEN_EOF)
        {
            current = process_redir(cmds[i], current);
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
