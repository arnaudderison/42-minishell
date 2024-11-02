/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:28:37 by aderison          #+#    #+#             */
/*   Updated: 2024/11/02 16:28:29 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	parsing(t_token *tokens)
{
	if (!tokens)
		return (PTR_NULL);
	if(tokens->type == TOKEN_EOF)
		return (UNKNOWN);
	if (!is_pipe_syntax(tokens) || !is_redir_syntax(tokens))
		return (FAILED);
	return (SUCCESS);
}
