/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:12:21 by aderison          #+#    #+#             */
/*   Updated: 2024/11/01 16:58:43 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	is_redir_op(t_token *token)
{
	return (token->type == TOKEN_REDIR_APP || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT
		|| token->type == TOKEN_REDIR_HEREDOC);
}

t_status	is_redir_syntax(t_token *tokens)
{
	t_token	*token;

	if (!tokens)
		return (PTR_NULL);
	token = tokens;
	while (token && token->type != TOKEN_EOF)
	{
		if (is_redir_op(token) == SUCCESS
			&& is_operator(token->next) == SUCCESS)
		{
			ft_printf_fd(2,
				RED "minish: " YELLOW "syntax error " RESET "near unexpected token \'%s\'\n",
				token->next->value);
			return (FAILED);
		}
		token = token->next;
	}
	return (SUCCESS);
}
