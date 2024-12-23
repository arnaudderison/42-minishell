/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:23:42 by aderison          #+#    #+#             */
/*   Updated: 2024/12/07 00:35:25 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enum.h"
# include "libft.h"
# include "structure.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

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
void		free_tokens(t_token *tokens, const char *input);
t_status	free_env(t_env *env);

// Tokeninsation
void		add_token(t_token **tokens, t_token_type type, char *value,
				t_lexer *lexer);
void		create_tokenisation(t_token **tokens, t_lexer *lexer);
void		create_word_token(t_lexer *lexer, t_token **tokens, int start_word);
void		manage_quote(t_token **tokens);

// parsing
t_bool		handle_parsing(const char *input, t_shell *sh);
t_status	is_operator(t_token *token);
t_status	is_redir_syntax(t_token *tokens);
t_status	is_pipe_syntax(t_token *tokens);
t_status	parsing(t_token *tokens);
void		print_parse_error(char *value);

// environment
t_status	add_var_env(char *name, char *value, t_env **envp);
t_env		*init_envp(char **envp);
char		*get_env(char *name, t_env *envp);

// expansion
t_status	get_var_name(t_state_expansion *state, int start);
char		*expand_input(char *input, t_env *envp);

// builtins
t_status	unset(t_shell *sh, char **args);
t_status	export(char *var, t_shell shell);
t_status	echo(char **args, t_bool endl);

// Signals
void		setup_prompt_signals(void);
void		handle_sigint_prompt(int sigint);

#endif