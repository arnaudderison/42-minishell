/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:28:37 by aderison          #+#    #+#             */
/*   Updated: 2024/11/01 17:05:20 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	parsing(t_token *tokens)
{
	if (!tokens)
		return (PTR_NULL);
	is_redir_syntax(tokens);
	return (SUCCESS);
}
