/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokenisation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:54:38 by aderison          #+#    #+#             */
/*   Updated: 2024/10/21 12:36:38 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_currentchar(t_lexer *lexer)
{
	return (lexer->input[lexer->position]);
}

static char	next_char(t_lexer *lexer)
{
	return (lexer->input[lexer->position++]);
}

static t_token_type	get_operator(t_lexer *lexer)
{
	char	c;

	c = get_currentchar(lexer);
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '\'')
		return (TOKEN_QUOTE);
	if (c == '\"')
		return (TOKEN_DQUOTE);
	if (c == '<' && lexer->input[lexer->position + 1] == '<')
		return (TOKEN_REDIR_HEREDOC);
	if (c == '<')
		return (TOKEN_REDIR_IN);
	if (c == '>' && lexer->input[lexer->position + 1] == '>')
		return (TOKEN_REDIR_APP);
	if (c == '>')
		return (TOKEN_REDIR_OUT);
	if (c == '\0')
		return (TOKEN_EOF);
	return (NAO);
}

static char	*get_char_with_token(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_QUOTE)
		return ("\'");
	if (type == TOKEN_DQUOTE)
		return ("\"");
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_REDIR_APP)
		return (">>");
	if (type == TOKEN_REDIR_HEREDOC)
		return ("<<");
	return (NULL);
}

void	create_tokenisation(t_token **tokens, t_lexer *lexer)
{
	int	start_word;

	while (get_operator(lexer) != TOKEN_EOF)
	{
		if (get_operator(lexer) != NAO)
		{
			add_token(tokens, get_operator(lexer),
				get_char_with_token(get_operator(lexer)), lexer);
			next_char(lexer);
		}
		if (ft_isspace(get_currentchar(lexer)))
			while (ft_isspace(get_currentchar(lexer)))
				next_char(lexer);
		if (get_operator(lexer) == NAO)
		{
			start_word = lexer->position;
			while (!ft_isspace(get_currentchar(lexer))
				&& get_operator(lexer) == NAO)
				next_char(lexer);
			create_word_token(lexer, tokens, start_word);
		}
	}
	if (get_operator(lexer) == TOKEN_EOF)
		add_token(tokens, TOKEN_EOF, NULL, lexer);
}
