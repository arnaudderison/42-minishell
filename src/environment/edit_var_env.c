/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_var_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:03:42 by aderison          #+#    #+#             */
/*   Updated: 2024/12/25 14:40:55 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	edit_var_env(char *name, char *value, t_env **envp)
{
	t_env	*tmp;

	if (!name || !value || !envp)
		return (PTR_NULL);
	tmp = *envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0
			&& ft_strlen(tmp->name) == ft_strlen(name))
		{
			ft_free(1, &tmp->value);
			tmp->value = value;
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (FAILED);
}
