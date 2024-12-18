/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:23:42 by aderison          #+#    #+#             */
/*   Updated: 2024/12/18 17:09:05 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "enum.h"
# include "libft.h"
# include "structure.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
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
}				t_bool;

// error and free fct
void			print_error(t_error err, const char *file, int line);
void			free_tokens(t_token *tokens, const char *input);
t_status		free_env(t_env *env);

// Tokeninsation
void			add_token(t_token **tokens, t_token_type type, char *value,
					t_lexer *lexer);
void			create_tokenisation(t_token **tokens, t_lexer *lexer);
void			create_word_token(t_lexer *lexer, t_token **tokens,
					int start_word);
void			manage_quote(t_token **tokens);

// parsing
t_bool			handle_parsing(const char *input, t_shell *sh);
t_status		is_operator(t_token *token);
t_status		is_redir_syntax(t_token *tokens);
t_status		is_pipe_syntax(t_token *tokens);
t_status		parsing(t_token *tokens);
void			print_parse_error(char *value);

// environment
t_status		add_var_env(char *name, char *value, t_env **envp);
t_status		edit_var_env(char *name, char *value, t_env **envp);
t_env			*init_envp(char **envp);
char			*get_env(char *name, t_env *envp);
static t_bool	is_new_var(t_shell *shell, char *name);
void			set_var_env(char *name, char *value, t_shell *shell);

// expansion
t_status		get_var_name(t_state_expansion *state, int start);
char			*expand_input(char *input, t_env *envp);

// builtins
t_status		unset(t_shell *sh, char **args);
t_status		export(t_shell *shell, char **args);
t_status		unset(t_shell *sh, char **args);
t_status		echo(char **args, int endl);
int				is_endl_echo(char **arg, int nb);
t_status		env(t_env *envp);
t_status		cd(char *path, t_shell *sh);
t_status		execb(char **cmd, t_shell *shell);

// Signals
void			setup_prompt_signals(void);
void			handle_sigint_prompt(int sigint);

#endif