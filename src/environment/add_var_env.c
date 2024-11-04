/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:32:53 by aderison          #+#    #+#             */
/*   Updated: 2024/11/04 15:32:57 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	add_var_env(char *name, char *value, t_env **envp)
{
	t_env	*new;
	t_env	*tmp;

	if (!name || !value || !envp)
		return (PTR_NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (MALLOC);
	new->name = name;
	new->value = value;
	new->next = NULL;
	if (!*envp)
		*envp = new;
	else
	{
		tmp = *envp;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
}
