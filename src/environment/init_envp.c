/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:24:19 by aderison          #+#    #+#             */
/*   Updated: 2024/11/03 19:33:25 by aderison         ###   ########.fr       */
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

t_env	*init_envp(char **envp)
{
	t_env	*env;
	char	*name;
	char	*equals;

	env = NULL;
	if (!envp || !*envp)
		return (NULL);
	while (*envp)
	{
		equals = ft_strrchr(*envp, '=');
		name = ft_substr(*envp, 0, equals - *envp);
		add_var_env(name, equals + 1, &env);
		envp++;
	}
	return (env);
}
