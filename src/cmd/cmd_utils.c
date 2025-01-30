/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:03:44 by plachard          #+#    #+#             */
/*   Updated: 2025/01/30 23:36:57 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->path)
		ft_free(1, &cmd->path);
	if (cmd->cmd)
		ft_free_matrice(1, &cmd->cmd);
	if (cmd->in)
		ft_free(2, &cmd->in->file, &cmd->in);
	if (cmd->out)
		ft_free(2, &cmd->out->file, &cmd->out);
	if (cmd->heredoc)
		ft_free(1, &(cmd->heredoc));
	ft_free(1, &cmd);
}

void	free_cmd_array(t_cmd **cmd_tab, int status)
{
	int	i;

	if (!cmd_tab)
		return ;
	i = -1;
	while (cmd_tab[++i])
		free_cmd(cmd_tab[i]);
	if (cmd_tab)
	{
		free(cmd_tab);
		cmd_tab = NULL;
	}
	if (status == -1)
		return ;
	exit(status);
}

int	pipe_count(t_token *token_lst)
{
	int	count;

	count = 0;
	if (!token_lst)
		return (0);
	while (token_lst)
	{
		if (token_lst->type == TOKEN_PIPE)
			++count;
		token_lst = token_lst->next;
	}
	return (count);
}

int	cmd_args_count(t_token *token_lst)
{
	int	count;

	count = 0;
	if (!token_lst)
		return (0);
	while (token_lst && token_lst->type != TOKEN_PIPE)
	{
		if (token_lst->type == TOKEN_WORD)
			++count;
		token_lst = token_lst->next;
	}
	return (count);
}

void	init_redir(t_cmd *cmd)
{
	cmd->in = NULL;
	cmd->out = NULL;
	cmd->heredoc = NULL;
}
