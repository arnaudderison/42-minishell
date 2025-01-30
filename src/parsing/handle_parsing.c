/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:00:31 by aderison          #+#    #+#             */
/*   Updated: 2025/01/28 19:53:36 by aderison         ###   ########.fr       */
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
	// ft_printf("NEW INPUT: [%s]\n", input);
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

t_bool	handle_parsing(const char *input, t_shell *sh)
{
	t_lexer	*lexer;
	t_token	*tokens;
	char *saved_input;

	lexer = NULL;
	tokens = NULL;
	saved_input = ft_strdup(input);
	if (!input)
		exit(EXIT_FAILURE);
	lexer = create_lexer((const char *)clean_quote(expand_input((char *)input,
					sh->envp, sh)));
	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (free_env(sh->envp), ft_free(1, &lexer), exit(EXIT_FAILURE),
			false);
	init_tokens(tokens, sh);
	create_tokenisation(&(sh->tokens), lexer);
	manage_quote(&(sh->tokens));
	if(!parsing(sh->tokens))
		return (false);
	if (!tokens_to_cmd(sh))
		return (free_tokens(sh->tokens, NULL), ft_free(2, &(lexer->input),&lexer), false);
	if(!(pipe_count(sh->tokens) == 0 && sh->cmds[0]->in && sh->cmds[0]->in->is_heredoc))
	{
		add_history(saved_input);
		ft_free(1, &saved_input);
	}
	return (free_tokens(sh->tokens, NULL), ft_free(2, &(lexer->input),&lexer), true);
}
