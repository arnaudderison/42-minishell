/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:27:35 by aderison          #+#    #+#             */
/*   Updated: 2024/11/03 19:21:30 by aderison         ###   ########.fr       */
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

/*
 * === Expansion ===
 * c'est hypothetique
 */
typedef struct s_expand
{
	char			*str;
	int				current_pos;
	int				second_pos;
	char			*expanded;
	char			*var_name;
	char			*var_value;
}					t_expand;

typedef struct s_shell
{
	t_token			*tokens;
	t_env			*envp;
	// char *home;
}					t_shell;

#endif