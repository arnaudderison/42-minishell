/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokeniser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:00:31 by aderison          #+#    #+#             */
/*   Updated: 2024/10/22 13:05:06 by aderison         ###   ########.fr       */
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

t_bool	tokeniser(const char *input)
{
	t_lexer	*lexer;
	t_token	*tokens;
	t_token	*tmp;

	lexer = NULL;
	tokens = NULL;
	if (!input)
	{
		print_error(ERR_NULL_PTR, "tokeniser.c", 48);
		exit(EXIT_FAILURE);
	}
	lexer = create_lexer(input);
	tokens = malloc(sizeof(t_token));
	if (!tokens)
	{
		print_error(ERR_MALLOC, "tokeniser.c", 55);
		ft_free(1, &input);
		exit(EXIT_FAILURE);
	}
	tokens->type = NAO;
	tokens->next = NULL;
	tokens->value = NULL;
	create_tokenisation(&tokens, lexer);
	manage_quote(&tokens);
	// START DEBUG
	tmp = tokens;
	while (tmp)
	{
		ft_printf("value: [%s], type: %d\n", tmp->value, tmp->type);
		tmp = tmp->next;
	}
	// END DEBUG
	free_tokens(tokens, input);
	ft_free(1, &lexer);
	return (true);
}
