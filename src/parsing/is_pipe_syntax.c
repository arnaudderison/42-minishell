/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:53:19 by aderison          #+#    #+#             */
/*   Updated: 2024/11/02 15:49:33 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	is_start_pipe(t_token *tokens)
{
	if (!tokens)
		return (PTR_NULL);
	if (tokens->type == TOKEN_PIPE)
		return (SUCCESS);
	return (FAILED);
}

static t_status	is_end_pipe(t_token *tokens)
{
	t_token	*token;

	if (!tokens)
		return (PTR_NULL);
	token = tokens;
	while (token && token->next->type != TOKEN_EOF)
		token = token->next;
	if (token->type == TOKEN_PIPE)
		return (SUCCESS);
	return (FAILED);
}

static t_status	is_double_pipe(t_token *tokens)
{
	t_token	*token;

	if (!tokens)
		return (PTR_NULL);
	token = tokens;
	while (token && token->type != TOKEN_EOF)
	{
		if (token->type == TOKEN_PIPE && token->next->type == TOKEN_PIPE)
			return (SUCCESS);
		token = token->next;
	}
	return (FAILED);
}

t_status	is_pipe_syntax(t_token *tokens)
{
	if (!tokens)
		return (PTR_NULL);
	if (is_start_pipe(tokens) == SUCCESS)
		return (print_parse_error(tokens->value), FAILED);
	if (is_end_pipe(tokens) == SUCCESS)
		return (print_parse_error("|"), FAILED);
	if (is_double_pipe(tokens) == SUCCESS)
	{
		ft_printf(BLUE "[+] Operator OR is not available\n" RESET);
		return (print_parse_error("|"), FAILED);
	}
	return (SUCCESS);
}
