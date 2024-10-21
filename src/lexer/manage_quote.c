/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:08:17 by aderison          #+#    #+#             */
/*   Updated: 2024/10/21 20:14:48 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_char_int_quote(t_token *tokens, t_token_type quote_type)
{
	t_token			*token;
	unsigned int	count_char;

	token = NULL;
	count_char = 0;
	token = tokens;
	while (token && token->type != quote_type)
	{
		count_char += ft_strlen(token->value);
		token = tokens->next;
	}
	return (count_char);
}

static void dispatch_value(t_token **tokens, t_token_type quote_type)
{
    t_token	*token;
    t_token	*tmp_token;
	char *new_value;
	char *tmp_value;
	int i;

	i = 0;
    token = (*tokens)->next;
    tmp_value = NULL;
    new_value = ft_strdup("");
    while(token && token->type != quote_type)
    {	
		tmp_value = ft_strjoin(new_value, token->value);
		ft_free(1, &new_value);
		new_value = tmp_value;
        token = token->next;
		++i;
    }
	ft_free(1, (*tokens)->value);
	(*tokens)->value = new_value;
	(*tokens)->type = TOKEN_WORD;
	(*tokens)->next = token->next;

	token = (*tokens)->next;
	while(i + 1 > 0)
	{
		tmp_token = token->next;
		ft_free(1, &token);
		token = tmp_token;
	}
}

void	manage_quote(t_token **tokens, const char *input)
{
	t_token	*token;
	t_token	*new_token;

	token = *tokens;
	// new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (print_error(ERR_MALLOC, "manage_quote.c", 73),
			free_tokens(tokens, input), exit(EXIT_FAILURE));
	while (token)
	{
		if (token->type == TOKEN_QUOTE || token->type == TOKEN_DQUOTE)
			dispatch_value(&token, token->type);
		token = token->next;
	}
}
