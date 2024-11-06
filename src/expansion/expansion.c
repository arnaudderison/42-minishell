/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:43:56 by aderison          #+#    #+#             */
/*   Updated: 2024/11/07 20:24:38 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	init_expand(char *input, t_expand **exp)
{
	if (!input)
		return (PTR_NULL);
	*exp = malloc(sizeof(t_expand));
	if (!exp)
		return (MALLOC);
	(*exp)->input = input;
	(*exp)->current_pos = 0;
	(*exp)->offset = 0;
	(*exp)->expanded = ft_strdup("");
	(*exp)->var_name = NULL;
	(*exp)->var_value = NULL;
	return (SUCCESS);
}

static t_status	expand_txt(t_expand *exp)
{
	char	*tmp_value;
	char	*tmp_exp;

	tmp_value = NULL;
	tmp_exp = NULL;
	if (!exp)
		return (PTR_NULL);
	tmp_exp = exp->expanded;
	exp->offset = exp->current_pos;
	while (exp->input[exp->offset] && exp->input[exp->offset] != '$'
		&& exp->input[exp->offset] != '\'')
		exp->offset++;
	tmp_value = ft_substr(exp->input, exp->current_pos, exp->offset
			- exp->current_pos);
	exp->current_pos = exp->offset;
	exp->expanded = ft_strjoin(tmp_exp, tmp_value);
	ft_free(2, &tmp_exp, &tmp_value);
	return (SUCCESS);
}

static t_status	expand_quote(t_expand *exp)
{
	char	*tmp_value;
	char	*tmp_exp;

	tmp_value = NULL;
	tmp_exp = NULL;
	if (!exp)
		return (PTR_NULL);
	tmp_exp = exp->expanded;
	exp->offset = exp->current_pos;
	exp->offset++;
	while (exp->input[exp->offset] && exp->input[exp->offset] != '\'')
		exp->offset++;
	tmp_value = ft_substr(exp->input, exp->current_pos, exp->offset
			- exp->current_pos);
	exp->current_pos = exp->offset;
	exp->expanded = ft_strjoin(tmp_exp, tmp_value);
	ft_free(2, &tmp_exp, &tmp_value);
	return (SUCCESS);
}

static t_status	insert_name_env(t_expand *exp, int start)
{
	int		i;
	char	*name;

	if (!exp)
		return (PTR_NULL);
	i = 0;
	while (exp->input[start + i] && (ft_isalnum(exp->input[start + i])
			|| exp->input[start + i] == '_'))
		i++;
	name = ft_substr(exp->input, start, i);
	exp->current_pos += i;
	exp->var_name = name;
	return (SUCCESS);
}

char	*expand_input(char *input, t_env *envp)
{
	t_expand	*exp;
	char		*tmp;

	if (!input)
		return (NULL);
	init_expand(input, &exp);
	while (exp->input[exp->current_pos])
	{
		if (exp->input[exp->current_pos] == '\'')
			expand_quote(exp);
		if (exp->input[exp->current_pos] != '$')
			expand_txt(exp);
		if (exp->input[exp->current_pos++] == '$')
		{
			insert_name_env(exp, exp->current_pos);
			exp->var_value = get_env(exp->var_name, envp);
			if (!exp->var_value)
				exp->var_value = "";
			tmp = exp->expanded;
			exp->expanded = ft_strjoin(tmp, exp->var_value);
			ft_free(2, &(exp->var_name), &tmp);
		}
	}
	return (tmp = exp->expanded, ft_free(1, &exp), tmp);
}
