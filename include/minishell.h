/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:23:42 by aderison          #+#    #+#             */
/*   Updated: 2025/01/28 19:37:22 by aderison         ###   ########.fr       */
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
# include <sys/wait.h>
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
t_status	is_redir_op(t_token *token);
t_status	is_redir_syntax(t_token *tokens);
t_status	is_pipe_syntax(t_token *tokens);
t_status	parsing(t_token *tokens);
void		print_parse_error(char *value);
char		*clean_quote(const char *str);

// environment
t_status	add_var_env(char *name, char *value, t_env **envp);
t_status	edit_var_env(char *name, char *value, t_env **envp);
t_env		*init_envp(char **envp);
char		*get_env(char *name, t_env **envp);
t_bool		is_new_var(t_shell *sh, char *name);
void		set_var_env(char *name, char *value, t_shell *shell);
char 		*get_path(t_shell *sh);

// expansion
t_status	get_var_name(t_state_expansion *state, int start);
char		*expand_input(char *input, t_env *envp, t_shell *sh);

// builtins
t_status	unset(t_shell *sh, char **args);
int			is_valid_identifier(const char *str);
t_status	export(t_shell *shell, char **args);
t_status	unset(t_shell *sh, char **args);
t_status	echo(char **args, int endl);
int			is_endl_echo(char **arg, int nb);
t_status	env(t_env *envp);
t_status	cd(char *path, t_shell *sh);
t_status	execb(char **cmd, t_shell *shell);
void		pwd(void);
t_status	print_env(t_env *envp);
void exitb(char **cmd, t_shell *sh);

// signals
void		setup_prompt_signals(void);
void		handle_sigint_prompt(int sigint);
void		restore_default_signals(void);
void		setup_exec_signals(void);
void		handle_sigint_child(int sigint);
void		handle_sigint_parent(int sigint);
void restore_sigquit(int sig);
void handle_sigquit(int sig);

// exec
// commandes
void		free_cmd(t_cmd *cmd);
int			pipe_count(t_token *token_lst);
t_status	access_cmd(t_cmd **cmd_tab);
int			cmd_args_count(t_token *token_lst);
t_cmd		**init_cmds(int cmd_count);
t_token		*find_cmd(t_cmd *cmd, t_token *token_lst);
t_status	set_cmd(t_cmd **cmd_tab, t_token *token_lst);
t_token		*set_redir(t_cmd **cmd, t_token *current);
t_status 	tokens_to_cmd(t_shell *shell);
void		free_cmd_array(t_cmd **cmd_tab, int status);

// redirections
t_token		*next_token(t_token *current);
t_bool		valid_fd(t_cmd *cmd, int redir_type);
void		close_fd(t_cmd *cmd);
t_bool		check_fd(t_cmd *cmd, int redir_type, const char *file);
t_status	add_redir(t_cmd *cmd, int redir_type, char *file);
void		clear_redir(t_token *redir);
void		free_redir(t_cmd *cmd, int type);
t_bool		assign_redir(t_cmd *cmd, t_redir *redir);

// access
char		**all_path(char *str_env);
t_status	cmds_path(t_cmd **cmd_tab, char **env);
t_status	set_path(t_cmd *cmd, char **env);
t_status	access_cmd(t_cmd **cmd_tab);

// exec
void		process_pipe(t_cmd *cmd1, t_cmd *cmd2);
int			execute_cmds(t_cmd **cmds);
int handle_heredoc(char *delimiter);

// utils
char		*cmd_path(t_cmd *cmd, char **env);
void		print_redir(t_cmd *cmd);
void		display_cmds(t_cmd **cmd_tab);
void		print_tokens(t_token *token);

// flemme
/*
 * Fonction qui marque un token de redirection comme inutilisable (NAO).
 */
void		clear_redir_token(t_token *redir);

/*
 * Libère les ressources associées à une redirection dans une commande.
 */
void		free_redir_cmd(t_cmd *cmd, int type);

/*
 * Met à jour la redirection d'une commande en fonction du type.
 */
t_bool		update_redir(t_cmd *cmd, t_redir *redir);

/*

	* Ouvre un fichier pour une redirection et retourne le descripteur de fichier (fd).
 */
int			open_redir_fd(t_redir new_redir);

/*

	* Crée et initialise une nouvelle redirection avec le type et le fichier spécifié.
 */
t_redir		*create_redir(int redir_type, char *file);

/*
 * Ajoute une redirection à une commande.
 */
t_status	add_redir(t_cmd *cmd, int redir_type, char *file);

/*
 * Traite un token de redirection et l'associe à la commande correspondante.
 */
t_token		*process_redir(t_cmd *cmd, t_token *current);

/*
 * Gère les redirections et les pipes dans la liste de tokens.
 */
t_token		*set_redir(t_cmd **cmd, t_token *current);
#endif
