/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:57:58 by aderison          #+#    #+#             */
/*   Updated: 2024/11/01 17:17:57 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	is_operator(t_token *token)
{
	return (token->type == TOKEN_REDIR_APP || token->type == TOKEN_REDIR_IN
		|| token->type == TOKEN_REDIR_OUT || token->type == TOKEN_REDIR_HEREDOC
		|| token->type == TOKEN_PIPE);
}
