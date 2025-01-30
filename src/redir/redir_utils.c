/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:56:33 by plachard          #+#    #+#             */
/*   Updated: 2025/01/30 23:59:50 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_redir_token(t_token *redir)
{
	if (!redir)
		return ;
	redir->type = NAO;
	if (redir->next)
		redir->next->type = NAO;
}

static void	free_redir_cmd(t_cmd *cmd, int type)
{
	t_redir	**redir;

	if (type == TOKEN_REDIR_IN)
		redir = &cmd->in;
	else if (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_APP)
		redir = &cmd->out;
	else
		return ;
	if (*redir)
		ft_free(2, &(*redir)->file, redir);
}

t_bool	update_redir(t_cmd *cmd, t_redir *redir)
{
	t_redir	**redir_ptr;

	if (redir->type == TOKEN_REDIR_IN)
		redir_ptr = &cmd->in;
	else if (redir->type == TOKEN_REDIR_OUT || redir->type == TOKEN_REDIR_APP)
		redir_ptr = &cmd->out;
	else if (redir->type == TOKEN_REDIR_HEREDOC)
		redir_ptr = &cmd->heredoc;
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
		return (-1);
	if (new_redir.type == TOKEN_REDIR_IN)
		fd = open(new_redir.file, O_RDONLY);
	else if (new_redir.type == TOKEN_REDIR_OUT)
		fd = open(new_redir.file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (new_redir.type == TOKEN_REDIR_APP)
		fd = open(new_redir.file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (new_redir.type == TOKEN_REDIR_HEREDOC)
		fd = -1;
	else
		return (-1);
	if (fd < 0)
		ft_printf("%s: no file or directory with this name\n", new_redir.file);
	return (fd);
}
