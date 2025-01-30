/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:28:37 by aderison          #+#    #+#             */
/*   Updated: 2025/01/30 22:57:09 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	parsing(t_token *tokens)
{
	if (!tokens)
		return (PTR_NULL);
	if (tokens->type == TOKEN_EOF)
		return (UNKNOWN);
	if (!is_redir_syntax(tokens) || !is_pipe_syntax(tokens))
		return (FAILED);
	return (SUCCESS);
}
