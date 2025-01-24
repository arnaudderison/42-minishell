
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

void	clear_redir_token(t_token *redir)
{
	if (!redir)
		return ;
	redir->type = NAO;
	if (redir->next)
		redir->next->type = NAO;
}

// else if (redir->type == TOKEN_REDIR_HEREDOC)
void	free_redir_cmd(t_cmd *cmd, int type)
{
	t_redir **redir;

	if (type == TOKEN_REDIR_IN)
		redir = &cmd->in;
	else if (type == TOKEN_REDIR_OUT)
		redir = &cmd->out;
	else if (type == TOKEN_REDIR_APP)
		redir = &cmd->append;
	else
		return;
	if (*redir)
	{
		ft_free(1, (*redir)->file);
		ft_free(1, *redir);
		// = ft_free(2, (*redir)->file, *redir )
		*redir = NULL;
	}
}

t_bool	update_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir **redir_ptr;

	if (redir->type == TOKEN_REDIR_IN)
		redir_ptr = &cmd->in;
	else if (redir->type == TOKEN_REDIR_OUT)
		redir_ptr = &cmd->out;
	else if (redir->type == TOKEN_REDIR_APP)
		redir_ptr = &cmd->append;
	// else if (redir->type == TOKEN_REDIR_HEREDOC) // heredoc ?
	else
		return (false);
	free_redir_cmd(cmd, redir->type);
	*redir_ptr = redir;
	return (true);
}

int	open_redir_fd(t_redir new_redir)
{
	int	fd;

	if (!new_redir.type || !new_redir.file)
		return(-1);
	if (new_redir.type == TOKEN_REDIR_IN)
		fd = open(new_redir.file, O_RDONLY);
	else if (new_redir.type == TOKEN_REDIR_OUT)
		fd = open(new_redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (new_redir.type == TOKEN_REDIR_APP)
		fd = open(new_redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	//else if (new_redir.type == TOKEN_REDIR_HEREDOC) // heredoc ?
	else
		return (-1);
	if (fd < 0)
		ft_printf("%s: no file or directory with this name\n", new_redir.file);
	return(fd);
}

void	print_redir(t_cmd *cmd)
{
	if (!cmd)
	{
		printf("Commande vide.\n");
		return ;
	}

	if (cmd->in)
	{
		printf("  Redirection entrée (<): %s\n", cmd->in->file);
	}
	else
	{
		printf("  Pas de redirection entrée (<)\n");
	}

	if (cmd->out)
	{
		printf("  Redirection sortie (>): %s\n", cmd->out->file);
	}
	else
	{
		printf("  Pas de redirection sortie (>)\n");
	}

	if (cmd->append)
	{
		printf("  Redirection ajout (>>): %s\n", cmd->append->file);
	}
	else
	{
		printf("  Pas de redirection ajout (>>)\n");
	}

	if (cmd->heredoc)
	{
		printf("  Heredoc (<<): %s\n", cmd->heredoc->file);
	}
	else
	{
		printf("  Pas de Heredoc (<<)\n");
	}

	printf("\n");
}

void	close_fd(t_cmd *cmd)
{
	if (cmd->type == TOKEN_REDIR_IN)
		close(cmd->in->fd);
	else if (cmd->type == TOKEN_REDIR_OUT)
		close(cmd->out->fd);
	else if (cmd->type == TOKEN_REDIR_APP)
		close(cmd->append->fd);
	else if (cmd->type == TOKEN_REDIR_HEREDOC) // heredoc ?
		close(cmd->heredoc->fd);
}
