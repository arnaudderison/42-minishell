
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

	printf("create redir --------------\n");
	if (!file)
		return (NULL);
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
	{
		printf("redir malloc error\n");
		return(NULL);
	}
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
		ft_free(1, new_redir->file);
		ft_free(1, new_redir);
		printf("open file error\n");
		return(NULL);
	}
	return (new_redir);
}

t_status	add_redir(t_cmd *cmd, int redir_type, char *file)
{
	t_redir	*new_redir;

	printf("add redir --------------\n");
	if (!cmd || !file)
	{
		printf("add redir input error");
		return (FAILED);
	}
	new_redir = create_redir(redir_type, file);
	if (!new_redir)
		return (FAILED);
	if (!update_redir(cmd, new_redir))
    {
        printf("error assign redir to cmd\n");
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
            printf("Error adding redir to cmd\n");
            return (NULL);
        }
        //printf("Redirection ajoutée: type=%d, file=%s\n", current->type, current->next->value);
		clear_redir_token(current);
        printf("current             = %s\n", current->value);
        printf("current next        = %s\n", current->next->value);
        printf("current next next   = %s\n", current->next->next->value);
        new_current = current->next->next;
        if (!new_current) 
        {
            printf("current is NULL after reassignment\n");
            exit(1);
        }
        current = new_current;
    }
    else
    {
        current = current->next;
    }
    return current;
}

void process_pipe(t_cmd *cmd1, t_cmd *cmd2)
{
    int pipe_fds[2];

    // On crée un pipe si ni cmd1 ni cmd2 n'ont de redirection qui empêche l'établissement du pipe
    if (pipe(pipe_fds) < 0)
    {
        perror("pipe failed");
        return;
    }

    // Si cmd1 n'a pas de sortie, alors cmd1 va envoyer son output au pipe
    if (!cmd1->out)
    {
        cmd1->out = (t_redir *)malloc(sizeof(t_redir));
        if (!cmd1->out)
        {
            perror("malloc failed");
            return;
        }
        cmd1->out->fd = pipe_fds[1];
        cmd1->out->file = NULL; // Le fichier n'est pas nécessaire ici, puisque c'est un pipe
    }

    // Si cmd2 n'a pas de redirection d'entrée, alors cmd2 va lire depuis le pipe
    if (!cmd2->in)
    {
        cmd2->in = (t_redir *)malloc(sizeof(t_redir));
        if (!cmd2->in)
        {
            perror("malloc failed");
            return;
        }
        cmd2->in->fd = pipe_fds[0];
        cmd2->in->file = NULL; // Pas de fichier pour l'entrée, c'est un pipe
    }

    // Fermeture des descripteurs de pipe dans le parent après utilisation
    close(pipe_fds[0]);
    close(pipe_fds[1]);
}

/*
t_token	*set_redir(t_cmd **cmd, t_token *current)
{
	t_token	*head;
	int		i;

	if (!cmd || !current)
		return (NULL);
	head = current;
	i = 0;
	while (current && current->type != TOKEN_EOF)
	{
		while (current && current->type != TOKEN_PIPE && current->type != TOKEN_EOF)
        {
            current = process_redir(cmd[i], current); // Gestion des redirections
            if (!current)
                return (NULL);
        }
		if (current && current->type == TOKEN_PIPE)
		{
			current = current->next;
			process_pipe(cmd[i+1], cmd[i]);
			++i;
		}
	}
	return (head);
}
*/

t_token *set_redir(t_cmd **cmds, t_token *current)
{
    t_token *head;
    int i;

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
			printf("CURRENT TYPE = %d VALUE = %s\n", current->type, current->value);
            current = process_redir(cmds[i], current);
			printf("process redir -------\n");
            if (!current)
                return (NULL);
        }

        // Si un pipe est trouvé, on vérifie et on applique la logique des pipes
        if (current && current->type == TOKEN_PIPE)
        {
			printf("CURRENT TYPE = PIPE\n");
            // On saute le pipe
            current = current->next;
            
            // Si cmd[i] a un "out", il ne doit pas y avoir de pipe
            // Si cmd[i+1] a un "in", il ne doit pas y avoir de pipe
            if (!cmds[i]->out && !cmds[i + 1]->in)
            {
                process_pipe(cmds[i], cmds[i + 1]); // Gérer le pipe entre cmd[i] et cmd[i+1]
            }
			printf("process PIPE-------\n");
            ++i;
        }
    }
    return (head);
}