/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:29:57 by aderison          #+#    #+#             */
/*   Updated: 2024/10/31 16:55:23 by aderison         ###   ########.fr       */
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

/*
 * MALLOC use as return value when an failed malloc is detected
 * PTR_NULL use as return value when an pointer NULL is detected
 * UNKNOWN use as return value when an UNKNOWN error is detected
 * SUCCESS use as return value when the fonction has gone well
 * FAILED use as return value when the focntion has gone well
   without error but the return value must be negative
 */
typedef enum s_status
{
	FAILED = 0,
	SUCCESS = 1,
	MALLOC,
	PTR_NULL,
	UNKNOWN,
}	t_status;
#endif
