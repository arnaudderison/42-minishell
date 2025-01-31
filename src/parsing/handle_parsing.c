/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:00:31 by aderison          #+#    #+#             */
/*   Updated: 2025/01/31 02:32:56 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*create_lexer(const char *input)
{
	t_lexer	*lexer;

	lexer = NULL;
	if (!input)
		exit(EXIT_FAILURE);
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
	{
		print_error(ERR_MALLOC, "tokeniser.c", 28);
		ft_free(1, &input);
		exit(EXIT_FAILURE);
	}
	lexer->input = input;
	lexer->position = 0;
	lexer->last_token = NULL;
	return (lexer);
}

static void	init_tokens(t_token *tokens, t_shell *sh)
{
	tokens->type = NAO;
	tokens->next = NULL;
	tokens->value = NULL;
	sh->tokens = tokens;
}

static t_bool	init_lexer_and_tokens(const char *input, t_shell *sh,
		t_lexer **lexer, t_token **tokens)
{
	char	*expanded_input;

	expanded_input = expand_input((char *)input, sh);
	*lexer = create_lexer((const char *)clean_quote(expanded_input));
	if (!*lexer)
		return (false);
	*tokens = malloc(sizeof(t_token));
	if (!*tokens)
	{
		ft_free(1, lexer);
		return (false);
	}
	init_tokens(*tokens, sh);
	create_tokenisation(&(sh->tokens), *lexer);
	manage_quote(&(sh->tokens));
	return (true);
}

static void	handle_history(char *saved_input, t_shell *sh)
{
	if (!(pipe_count(sh->tokens) == 0 && sh->cmds[0]->in
			&& sh->cmds[0]->in->is_heredoc))
		add_history(saved_input);
	ft_free(1, &saved_input);
}

t_bool	handle_parsing(const char *input, t_shell *sh)
{
	t_lexer	*lexer;
	t_token	*tokens;
	char	*saved_input;

	if (!input)
		exit(EXIT_FAILURE);
	saved_input = ft_strdup(input);
	if (!init_lexer_and_tokens(input, sh, &lexer, &tokens))
		return (false);
	if (!parsing(sh->tokens))
		return (false);
	if (!tokens_to_cmd(sh))
	{
		free_tokens(sh->tokens, NULL);
		ft_free(2, &(lexer->input), &lexer);
		return (false);
	}
	handle_history(saved_input, sh);
	free_tokens(sh->tokens, NULL);
	ft_free(2, &(lexer->input), &lexer);
	return (true);
}
