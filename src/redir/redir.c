
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
    // printf("            CREATE REDIR\n");
	t_redir	*new_redir;

	if (!file)
    {
        printf("                file = null\n");
		return (NULL);
    }
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return(NULL);
	new_redir->type = redir_type;
	new_redir->file = strdup(file);
	if (!new_redir->file)
	{
		ft_free(1, new_redir);
		return(NULL);
	}
	new_redir->fd = open_redir_fd(*new_redir);
	if (new_redir->fd < 0)
	{
        // printf("                fd < 0\n");
		ft_free(1, &new_redir->file);
		ft_free(1, &new_redir);
		return(NULL);
	}
	return (new_redir);
}

t_status	add_redir(t_cmd *cmd, int redir_type, char *file)
{
    // printf("        ADD REDIR\n");
	t_redir	*new_redir;

	if (!cmd || !file)
		return (FAILED);
	new_redir = create_redir(redir_type, file);
	if (!new_redir)
    {
        // printf("        create redir failed\n");
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
    // printf("    PROCESS REDIR\n");
    t_token *new_current;

    if (is_redir_op(current))
    {
        if (!add_redir(cmd, current->type, current->next->value))
        {
            // printf("        add redir failed\n");
            cmd->exit_code = 1;
            clear_redir_token(current);
            return (current->next->next);
        }
        //printf("Redirection ajoutée: type=%d, file=%s\n", current->type, current->next->value);
		clear_redir_token(current);
        new_current = current->next->next;
        if (!new_current) 
            exit(1);
        current = new_current;
    }
    else
    {
        current = current->next;
    }
    return current;
}

t_token *set_redir(t_cmd **cmds, t_token *current)
{
    t_token *head;
    int i;

    // printf("SET REDIR\n");
    if (!cmds || !current)
        return (NULL);
    head = current;
    i = 0;

    // Parcours de la liste des tokens
    while (current && current->type != TOKEN_EOF)
    {
        while (current && current->type != TOKEN_PIPE && current->type != TOKEN_EOF)
        {
            // Gestion des redirections
            current = process_redir(cmds[i], current);
            if (!current)
            {
                printf("failed process_redir\n");
            }
        }

        // Si un pipe est trouvé, on vérifie et on applique la logique des pipes
        if (current && current->type == TOKEN_PIPE)
        {
            // On saute le pipe
            current = current->next;
            
            // Si cmd[i] a un "out", il ne doit pas y avoir de pipe
            // Si cmd[i+1] a un "in", il ne doit pas y avoir de pipe
            // if (!cmds[i]->out && !cmds[i + 1]->in)
            // {
            //     process_pipe(cmds[i], cmds[i + 1]); // Gérer le pipe entre cmd[i] et cmd[i+1]
            // }
            ++i;
        }
    }
    return (head);
}