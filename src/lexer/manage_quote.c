/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:08:17 by aderison          #+#    #+#             */
/*   Updated: 2025/01/15 16:58:46 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_unless_token(t_token **tokens, t_token *token)
{
	t_token	*tmp_token;
	t_token	*next_token;

	if (token->type == TOKEN_EOF)
		tmp_token = token;
	else
		tmp_token = token->next;
	token = (*tokens)->next;
	while (token != tmp_token && token->type != TOKEN_EOF)
	{
		next_token = token->next;
		ft_free(2, &token->value, &token);
		token = next_token;
	}
	(*tokens)->next = tmp_token;
}

static void	dispatch_value(t_token **tokens, t_token_type quote_type)
{
	t_token	*token;
	char	*new_value;
	char	*tmp_value;

	if (!(*tokens)->next)
		return ;
	if ((*tokens)->next->type == TOKEN_EOF)
		return ((*tokens)->type = TOKEN_EOF, ft_free(2, &(*tokens)->value,
				&(*tokens)->next));
	token = (*tokens)->next;
	tmp_value = NULL;
	new_value = ft_strdup("");
	while (token && token->value && token->type != quote_type)
	{
		tmp_value = ft_strjoin(new_value, token->value);
		ft_free(1, &new_value);
		new_value = tmp_value;
		tmp_value = ft_strjoin(new_value, " ");
		ft_free(1, &new_value);
		new_value = tmp_value;
		token = token->next;
	}
	ft_free(1, &((*tokens)->value));
	return ((*tokens)->value = new_value, (*tokens)->type = TOKEN_WORD,
		free_unless_token(tokens, token));
}

void	manage_quote(t_token **tokens)
{
	t_token	*token;

	if (!(*tokens) || !(*tokens)->value)
		return ;
	token = *tokens;
	while (token && token->value)
	{
		if (token->type == TOKEN_QUOTE || token->type == TOKEN_DQUOTE)
			dispatch_value(&token, token->type);
		token = token->next;
	}
}
