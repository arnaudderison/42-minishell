/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:27:35 by aderison          #+#    #+#             */
/*   Updated: 2024/11/13 18:16:24 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H


/*
 * === Tokenisation ===
 * this struct represents a token with t_token_type (look enum)
 */

typedef struct s_lexer
{
	const char		*input;
	int				position;
	t_token			*last_token;
}					t_lexer;

#endif