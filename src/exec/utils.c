// #include "minishell.h"

// bool	is_redir(t_token_type redir)
// {
// 	if (redir == TOKEN_REDIR_IN || redir == TOKEN_REDIR_OUT
// 		|| redir == TOKEN_REDIR_APP || redir == TOKEN_REDIR_HEREDOC)
// 		return (true);
// 	return (false);
// }

// t_token	*next_token(t_token *current)
// {
// 	if (current->next)
// 		return (current->next);
// 	return (NULL);
// }

// char	*cmd_path(t_cmd *cmd, char **env)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*path;

// 	if (!cmd)
// 		return (NULL);
// 	i = -1;
// 	while (env && env[++i])
// 	{
// 		tmp = ft_strjoin(env[i], "/");
// 		if (!tmp)
// 			exit(1);
// 		path = ft_strjoin(tmp, cmd->cmd[0]);
// 		if (!path)
// 		{
// 			ft_free(1, &tmp);
// 			exit(1);
// 		}
// 		if (access(path, X_OK) == 0)
// 			return (ft_free(1, &tmp), path);
// 		ft_free(2, &tmp, &path);
// 	}
// 	ft_printf(" command not found: %s\n", cmd->cmd[0]);
// 	return (NULL);
// }

// void	print_redir(t_cmd *cmd)
// {
// 	if (!cmd)
// 	{
// 		printf("Commande vide.\n");
// 		return ;
// 	}

// 	printf("Redirections pour la commande :\n");

// 	if (cmd->in)
// 	{
// 		printf("  Redirection entrée (<): %s\n", cmd->in->file);
// 	}
// 	else
// 	{
// 		printf("  Pas de redirection entrée (<)\n");
// 	}

// 	if (cmd->out)
// 	{
// 		printf("  Redirection sortie (>): %s\n", cmd->out->file);
// 	}
// 	else
// 	{
// 		printf("  Pas de redirection sortie (>)\n");
// 	}

// 	if (cmd->append)
// 	{
// 		printf("  Redirection ajout (>>): %s\n", cmd->append->file);
// 	}
// 	else
// 	{
// 		printf("  Pas de redirection ajout (>>)\n");
// 	}

// 	if (cmd->heredoc)
// 	{
// 		printf("  Heredoc (<<): %s\n", cmd->heredoc->file);
// 	}
// 	else
// 	{
// 		printf("  Pas de Heredoc (<<)\n");
// 	}

// 	printf("\n");
// }