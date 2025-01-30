/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:41:06 by plachard          #+#    #+#             */
/*   Updated: 2025/01/30 23:55:16 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	*alloc_redir(t_redir *new_redir, char *file)
{
	if (!file)
	{
		ft_printf("file = null\n");
		return (NULL);
	}
	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		exit(1);
	new_redir->file = strdup(file);
	if (!new_redir)
		exit(1);
	return (new_redir);
}

static t_redir	*create_redir(int redir_type, char *file)
{
	t_redir	*new_redir;

	new_redir = NULL;
	new_redir = alloc_redir(new_redir, file);
	if (!new_redir)
		exit(1);
	new_redir->type = redir_type;
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
	return (new_redir);
}

static t_status	add_redir(t_shell *sh, int redir_type, char *file, int i)
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
		handle_heredoc(file, sh);
		ft_free(1, &new_redir->file);
		new_redir->type = TOKEN_REDIR_IN;
		new_redir->fd = open("/tmp/heredoc_tmp", O_RDONLY);
	}
	if (!update_redir(sh->cmds[i], new_redir))
	{
		ft_printf("Est ce que ca failed ?\n");
		free(new_redir);
		return (FAILED);
	}
	return (SUCCESS);
}

static t_token	*process_redir(t_shell *sh, t_token *current, int i)
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
