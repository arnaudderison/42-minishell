/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 17:24:19 by aderison          #+#    #+#             */
/*   Updated: 2025/01/30 16:13:43 by arnaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(char *env_var, char *equals)
{
	return (ft_substr(env_var, 0, equals - env_var));
}

static char	*get_value_var(char *equals)
{
	return (ft_strdup(equals + 1));
}

static void	add_variable(char *env_var, t_env **env)
{
	char	*equals;
	char	*name;
	char	*value;

	equals = ft_strrchr(env_var, '=');
	if (!equals)
		return ;
	name = get_name(env_var, equals);
	if (!name)
		return ;
	value = get_value_var(equals);
	if (!value)
	{
		free(name);
		return ;
	}
	add_var_env(name, value, env);
}

t_env	*init_envp(char **envp)
{
	t_env	*env;

	env = NULL;
	while (*envp)
	{
		add_variable(*envp, &env);
		envp++;
	}
	return (env);
}
