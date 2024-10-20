/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:50:00 by aderison          #+#    #+#             */
/*   Updated: 2024/10/20 02:24:58 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*token;
	t_token	*next;

	token = NULL;
	if (!tokens)
		return ;
	token = tokens;
	while (token)
	{
		next = token->next;
		ft_free(2, &token->value, &token);
		token = next;
	}
}
