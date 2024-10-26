/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 00:40:41 by aderison          #+#    #+#             */
/*   Updated: 2024/10/26 18:56:10 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_word_token(t_lexer *lexer, t_token **tokens, int start_word)
{
	char	*value_word;

	value_word = NULL;
	value_word = malloc(sizeof(char) * ((lexer->position - start_word) + 1));
	if (!value_word)
		return (print_error(ERR_MALLOC, "create_tokenisation.c", 90),
			free_tokens(*tokens, lexer->input), exit(EXIT_FAILURE));
	ft_strlcpy(value_word, lexer->input + start_word, (lexer->position
			- start_word) + 1);
	add_token(tokens, TOKEN_WORD, value_word, lexer);
	ft_free(1, &value_word);
}

void	add_token(t_token **tokens, t_token_type type, char *value,
		t_lexer *lexer)
{
	t_token	*new_token;

	if (type == TOKEN_REDIR_APP || type == TOKEN_REDIR_HEREDOC)
		lexer->position++;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		print_error(ERR_MALLOC, "lexer/utils.c", 38);
		ft_free(1, &lexer->input);
		exit(EXIT_FAILURE);
	}
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	if ((*tokens)->type == NAO && (*tokens)->value == NULL)
	{
		ft_free(1, tokens);
		(*tokens) = new_token;
		lexer->last_token = new_token;
	}
	else
	{
		lexer->last_token->next = new_token;
		lexer->last_token = new_token;
	}
}
