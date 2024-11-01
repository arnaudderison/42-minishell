/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:23:42 by aderison          #+#    #+#             */
/*   Updated: 2024/11/01 18:47:04 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enum.h"
# include "libft.h"
# include "structure.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_INPUT_LENGHT 1024

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define RESET "\x1B[0m"

typedef enum s_bool
{
	false,
	true
}			t_bool;

// error and free fct
void		print_error(t_error err, const char *file, int line);

// Tokeninsation
void		free_tokens(t_token *tokens, const char *input);
void		add_token(t_token **tokens, t_token_type type, char *value,
				t_lexer *lexer);
void		create_tokenisation(t_token **tokens, t_lexer *lexer);
t_bool		tokeniser(const char *input);
void		create_word_token(t_lexer *lexer, t_token **tokens, int start_word);
void		manage_quote(t_token **tokens);

// parsing
t_status	is_operator(t_token *token);
t_status	is_redir_syntax(t_token *tokens);
t_status	parsing(t_token *tokens);

#endif