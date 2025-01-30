/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:57:58 by aderison          #+#    #+#             */
/*   Updated: 2025/01/30 22:56:59 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	is_operator(t_token *token)
{
	if (!token)
		return (PTR_NULL);
	return (token->type == TOKEN_REDIR_APP || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_REDIR_HEREDOC
		|| token->type == TOKEN_PIPE);
}
