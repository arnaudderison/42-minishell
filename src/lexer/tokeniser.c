/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:00:31 by aderison          #+#    #+#             */
/*   Updated: 2024/11/03 19:38:32 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*create_lexer(const char *input)
{
	t_lexer	*lexer;

	lexer = NULL;
	if (!input)
	{
		print_error(ERR_NULL_PTR, "tokeniser.c", 22);
		exit(EXIT_FAILURE);
	}
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

t_bool	tokeniser(const char *input, t_shell *sh)
{
	t_lexer	*lexer;
	t_token	*tokens;

	lexer = NULL;
	tokens = NULL;
	if (!input)
		exit(EXIT_FAILURE);
	lexer = create_lexer(input);
	tokens = malloc(sizeof(t_token));
	if (!tokens)
	{
		free_env(sh->envp);
		ft_free(2, &input, &lexer);
		exit(EXIT_FAILURE);
	}
	tokens->type = NAO;
	tokens->next = NULL;
	tokens->value = NULL;
	sh->tokens = tokens;
	create_tokenisation(&(sh->tokens), lexer);
	manage_quote(&(sh->tokens));
	parsing(sh->tokens);
	return (free_tokens(sh->tokens, input), ft_free(1, &lexer), true);
}
