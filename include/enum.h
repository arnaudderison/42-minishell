/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:29:57 by aderison          #+#    #+#             */
/*   Updated: 2024/10/31 16:31:27 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

typedef enum s_error
{
	ERR_MALLOC,
	ERR_NULL_PTR,
}	t_error;

/*
 * === TOKENISATION ===
 * use to identify token in an input
 * WORD is something other than an operator or pipe
 * PIPE             '|'
 * QUOTE            '''
 * DQUOTE           '"'
 * REDIR_IN         '<'
 * REDIR_OUT        '>'
 * REDIR_APP        '>>'
 * REDIR_HEREDOC    '<<'
 * NAO              NOT A OPERATOR
 */
typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_QUOTE,
	TOKEN_DQUOTE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APP,
	TOKEN_REDIR_HEREDOC,
	TOKEN_EOF,
	NAO,
}	t_token_type;

typedef enum s_status
{
	MALLOC,
	PTR_NULL,
	UNKNOWN,
	SUCCESS,
}	t_status;
#endif
