/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:24:19 by aderison          #+#    #+#             */
/*   Updated: 2024/12/20 19:13:12 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		equals = ft_strdup(ft_strrchr(*envp, '='));
		if (!equals)
		{
			envp++;
			continue ;
		}
		name = ft_strdup(ft_substr(*envp, 0, equals - *envp));
		if (!name)
		{
			envp++;
			continue ;
		}
		add_var_env(name, equals + 1, &env);
		envp++;
	}
	return (env);
}
