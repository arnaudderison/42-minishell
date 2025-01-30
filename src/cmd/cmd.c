/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 23:00:58 by plachard          #+#    #+#             */
/*   Updated: 2025/01/30 23:28:28 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*init_cmd(void)
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd = NULL;
	new_cmd->path = NULL;
	init_redir(new_cmd);
	new_cmd->exit_code = 0;
	return (new_cmd);
}

static t_cmd	**init_cmd_array(int cmd_count)
{
	t_cmd	**cmd_tab;
	int		i;

	cmd_tab = malloc(sizeof(t_cmd) * (cmd_count + 1));
	if (!cmd_tab)
		return (NULL);
	i = -1;
	while (++i < cmd_count)
	{
		cmd_tab[i] = init_cmd();
		if (!cmd_tab[i])
			free_cmd_array(cmd_tab, 1);
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

static t_token	*find_cmd(t_cmd *cmd, t_token *token_lst)
{
	int	j;

	cmd->cmd = malloc(sizeof(char *) * (cmd_args_count(token_lst) + 1));
	if (!cmd->cmd)
		return (NULL);
	j = 0;
	while (token_lst->type != TOKEN_EOF && token_lst->type != TOKEN_PIPE)
	{
		if (token_lst->type == TOKEN_WORD)
		{
			cmd->cmd[j] = strdup(token_lst->value);
			if (!cmd->cmd[j++])
				return (NULL);
		}
		token_lst = token_lst->next;
	}
	cmd->cmd[j] = NULL;
	if (token_lst->type == TOKEN_PIPE)
		token_lst = token_lst->next;
	else if ((token_lst->type == TOKEN_EOF))
		return (token_lst);
	return (token_lst);
}

static t_status	set_cmd(t_cmd **cmd_tab, t_token *token_lst)
{
	int	i;

	if (!cmd_tab || !token_lst)
		return (FAILED);
	i = 0;
	while (token_lst->type != TOKEN_EOF)
	{
		token_lst = find_cmd(cmd_tab[i], token_lst);
		if (!token_lst && i == 0)
			return (FAILED);
		++i;
	}
	cmd_tab[i] = NULL;
	return (SUCCESS);
}

t_status	tokens_to_cmd(t_shell *shell)
{
	t_token	*token_lst;

	token_lst = shell->tokens;
	if (!(token_lst))
		return (FAILED);
	shell->cmds = init_cmd_array(pipe_count(token_lst) + 1);
	if (!shell->cmds)
		return (FAILED);
	token_lst = set_redir(shell, token_lst);
	if (!set_cmd(shell->cmds, token_lst))
		return (FAILED);
	return (SUCCESS);
}
