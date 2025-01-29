/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:27:35 by aderison          #+#    #+#             */
/*   Updated: 2025/01/25 17:56:09 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

/*
 * === Tokenisation ===
 * this struct represents a token with t_token_type (look enum)
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_lexer
{
	const char		*input;
	int				position;
	t_token			*last_token;
}					t_lexer;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_state_expansion
{
	char			*input;
	char			*expanded;
	int				i;
	char			*var_name;
	char			*var_value;
	int				in_quote;
	int				in_dquote;
}					t_state_expansion;

typedef struct s_redir
{
	int type;   // Type de redirection (<, >, >>, <<)
	char *file; // Nom du fichier
	int				fd;
	int is_heredoc;
}					t_redir;

typedef struct s_cmd
{
	int				type;
	char			**cmd;
	char			*path;
	t_redir			*in;
	t_redir			*out;
	t_redir			*heredoc;
	t_redir			*append;
	int				exit_code;
}					t_cmd;

typedef struct s_shell
{
	t_token			*tokens;
	t_env			*envp;
	t_env			*user_env;
	t_cmd			**cmds;
	int				exit_code;
	char			**env_execve;		
}					t_shell;

/*
	PLAAAAAAAAACHAAAAAAAAAARD
*/

#endif
