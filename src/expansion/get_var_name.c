/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 02:58:24 by aderison          #+#    #+#             */
/*   Updated: 2024/12/03 20:09:10 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	get_var_name(t_state_expansion *state, int start)
{
	int		i;
	char	*name;

	i = 0;
	if (state->input[start + i] && ft_isdigit(state->input[start + i]))
	{
		++i;
		name = ft_substr(state->input, start, i);
		state->i += i;
		state->var_name = name;
		return (SUCCESS);
	}
	while (state->input[start + i] && (ft_isalnum(state->input[start + i])
			|| state->input[start + i] == '_'))
		i++;
	name = ft_substr(state->input, start, i);
	state->i += i;
	state->var_name = name;
	return (SUCCESS);
}
