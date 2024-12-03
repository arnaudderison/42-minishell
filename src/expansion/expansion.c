/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:43:56 by aderison          #+#    #+#             */
/*   Updated: 2024/12/03 03:20:25 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status init_expand(t_state_expansion *state, char *input)
{
	state->input = input;
	state->expanded = ft_strdup("");
	state->i = 0;
	state->var_name = NULL;
	state->var_value = NULL;
	state->in_quote = false;
	state->in_dquote = false;
	return (SUCCESS);
}

static t_status	expand_quote(t_state_expansion *state)
{
	char	*tmp_value;
	char	*tmp_exp;
	int		offset;

	tmp_value = NULL;
	tmp_exp = NULL;
	tmp_exp = state->expanded;
	offset = state->i + 1;
	while (state->input[offset] && state->input[offset] != '\'')
		offset++;
	tmp_value = ft_substr(state->input, state->i, ++offset - state->i);
	state->i = offset;
	state->expanded = ft_strjoin(tmp_exp, tmp_value);
	ft_free(2, &tmp_exp, &tmp_value);
	return (SUCCESS);
}

static t_status	expand_txt(t_state_expansion *state)
{
	char	*tmp_value;
	char	*tmp_exp;
	int		offset;

	tmp_value = NULL;
	tmp_exp = NULL;
	if(state->input[state->i] == '\"'){
		state->in_dquote = !(state->in_dquote);
	}
	tmp_exp = state->expanded;
	offset = state->i + 1;
	while (state->input[offset] && state->input[offset] != '$' && state->input[offset] != '\'')
	{
		if(state->input[offset] == '\"')
			state->in_dquote = !(state->in_dquote);
		offset++;
	}
	tmp_value = ft_substr(state->input, state->i, offset - state->i);
	state->i = offset;
	state->expanded = ft_strjoin(tmp_exp, tmp_value);
	ft_free(2, &tmp_exp, &tmp_value);
	return (SUCCESS);
}

static t_status handle_alias(t_state_expansion *state)
{
	char *tmp;
	
	if(!state->input[state->i + 1])
	{
		tmp = state->expanded;
		state->expanded = ft_strjoin(tmp, "$");
		state->i++;
		return (ft_free(1, &tmp), SUCCESS);
	}
	if(state->input[state->i + 1] == '$')
	{
		tmp = state->expanded;
		state->expanded = ft_strjoin(tmp, "$$");
		ft_free(1, &tmp);
		state->i += 2;
		return (SUCCESS);
	}
	return (FAILED);
}

char *expand_input(char *input, t_env *envp)
{
	t_state_expansion state;
	char *tmp;

	init_expand(&state, input);
	while(state.input[state.i])
	{
		if(state.input[state.i] == '\'' && !state.in_dquote)
			expand_quote(&state);
		if(state.input[state.i] != '$' && (state.input[state.i] != '\''  || state.in_dquote))
			expand_txt(&state);
		if (state.input[state.i] == '$')
		{
			if(handle_alias(&state))
				continue;
			get_var_name(&state, ++state.i);
			state.var_value = get_env(state.var_name, envp);
			if (!state.var_value)
				state.var_value = "";
			tmp = state.expanded;
			state.expanded = ft_strjoin(tmp, state.var_value);
			ft_free(2, &(state.var_name), &tmp);
		}
	}
	return (state.expanded);
}
