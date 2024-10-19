/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:29:57 by aderison          #+#    #+#             */
/*   Updated: 2024/10/19 21:45:04 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

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
}	t_token_type;

#endif
