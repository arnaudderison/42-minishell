
// #include "minishell.h"

// // t_redir *init_redir(t_token *redir)
// // {
// //     t_redir *new;

// //     new = malloc(sizeof(t_redir));
// //     if (!new)
// //         return (NULL);
// //     new->type = redir->type;
// //     if (redir->next)
// //         new->file = redir->next->value;
// //     else
// //         new->file = NULL;
// //     return (new);
// // }

// t_token	*next_token(t_token *current)
// {
// 	if (current->next)
// 		return (current->next);
// 	return (NULL);
// }

// bool	is_redir(t_token_type redir)
// {
// 	if (redir == TOKEN_REDIR_IN || redir == TOKEN_REDIR_OUT
// 		|| redir == TOKEN_REDIR_APP || redir == TOKEN_REDIR_HEREDOC)
// 		return (true);
// 	return (false);
// }

// bool	valid_fd(t_cmd *cmd, int redir_type)
// {
// 	int	fd;

// 	if (redir_type == TOKEN_REDIR_IN)
// 		fd = cmd->in->fd;
// 	else if (redir_type == TOKEN_REDIR_OUT)
// 		fd = cmd->out->fd;
// 	else if (redir_type == TOKEN_REDIR_APP)
// 		fd = cmd->append->fd;
// 	else if (redir_type == TOKEN_REDIR_HEREDOC) // heredoc ?
// 		fd = 0;
// 	if (fd < 0)
// 	{
// 		printf("fd < 0\n");
// 		return (false);
// 	}
// 	return (true);
// }

// void	close_fd(t_cmd *cmd)
// {
// 	if (cmd->type == TOKEN_REDIR_IN)
// 		close(cmd->in->fd);
// 	else if (cmd->type == TOKEN_REDIR_OUT)
// 		close(cmd->out->fd);
// 	else if (cmd->type == TOKEN_REDIR_APP)
// 		close(cmd->append->fd);
// 	else if (cmd->type == TOKEN_REDIR_HEREDOC) // heredoc ?
// 		close(cmd->heredoc->fd);
// }

// bool	check_fd(t_cmd *cmd, int redir_type, const char *file)
// {
// 	if (redir_type == TOKEN_REDIR_IN)
// 		cmd->in->fd = open(file, O_RDONLY);
// 	else if (redir_type == TOKEN_REDIR_OUT)
// 		cmd->out->fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else if (redir_type == TOKEN_REDIR_APP)
// 		cmd->append->fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else if (redir_type == TOKEN_REDIR_HEREDOC) // heredoc ?
// 		return (true);
// 	else
// 	{
// 		printf("token error\n");
// 		return (false);
// 	}
// 	if (valid_fd(cmd, redir_type))
// 	{
// 		printf("fd < 0\n");
// 		return (false);
// 	}
// 	close_fd(cmd);
// 	return (true);
// }

// t_status	add_redir(t_cmd *cmd, int redir_type, char *file)
// {
// 	t_redir	*new_redir;

// 	if (!cmd || !file)
// 		return (FAILED);
// 	if (!check_fd(cmd, redir_type, file))
// 		return (FAILED);
// 	new_redir = malloc(sizeof(t_redir));
// 	if (!new_redir)
// 		return (FAILED);
// 	new_redir->type = redir_type;
// 	new_redir->file = strdup(file);
// 	if (!new_redir->file)
// 	{
// 		free(new_redir);
// 		return (FAILED);
// 	}
// 	if (redir_type == TOKEN_REDIR_IN)
// 	{
// 		if (cmd->in)
// 		{
// 			free(cmd->in->file);
// 			free(cmd->in);
// 		}
// 		cmd->in = new_redir;
// 	}
// 	else if (redir_type == TOKEN_REDIR_OUT)
// 	{
// 		if (cmd->out)
// 		{
// 			free(cmd->out->file);
// 			free(cmd->out);
// 		}
// 		cmd->out = new_redir;
// 	}
// 	else if (redir_type == TOKEN_REDIR_APP)
// 	{
// 		if (cmd->append)
// 		{
// 			free(cmd->append->file);
// 			free(cmd->append);
// 		}
// 		cmd->append = new_redir;
// 	}
// 	else if (redir_type == TOKEN_REDIR_HEREDOC)
// 	{
// 		if (cmd->heredoc)
// 		{
// 			free(cmd->heredoc->file);
// 			free(cmd->heredoc);
// 		}
// 		cmd->heredoc = new_redir;
// 	}
// }

// void	clear_redir(t_token *redir)
// {
// 	redir->type = NAO;
// 	if (redir->next)
// 		redir->next->type = NAO;
// }

// /*  SET_REDIR

// 	IN = liste de t_token

// 	OUT = SUCCESS si

// 	1. alloue le tableau de s_cmd
// 	2. assigne les redirections des t_cmd
// 		modifie le type des tokens redirections et de leurs fichiers
// 	3. assigne le tableau de commande de chaque s_cmd
// */
// t_token	*set_redir(t_cmd **cmd, t_token *current)
// {
// 	t_token	*head;
// 	int		i;

// 	if (!cmd || !current)
// 		return (NULL);
// 	head = current;
// 	i = 0;
// 	while (current && current->type != TOKEN_EOF)
// 	{
// 		while (current && current->type != TOKEN_PIPE
// 			&& current->type != TOKEN_EOF)
// 		{
// 			if (is_redir(current->type))
// 			{
// 				if (!current->next)
// 					// Vérifie si next est valide avant d'accéder à `current->next->value`.
// 					return (printf("Erreur: token de redirection sans fichier associé\n"),
// 						NULL);
// 				if (!cmd[i])
// 					return (printf("Erreur: cmd[%d] non initialisée\n", i),
// 						NULL);
// 				if (!add_redir(cmd[i], current->type, current->next->value))
// 					return (printf("add_redir failed for cmd n°%d\n", i), NULL);
// 				printf("Redirection ajoutée: type=%d, file=%s\n", current->type,
// 					current->next->value);
// 				clear_redir(current);
// 				current = next_token(next_token(current));
// 			}
// 			else
// 				current = next_token(current);
// 		}
// 		if (current && current->type == TOKEN_PIPE)
// 		{
// 			current = next_token(current);
// 			++i;
// 		}
// 	}
// 	return (head);
// }
