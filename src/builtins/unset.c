/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:21:17 by aderison          #+#    #+#             */
/*   Updated: 2025/01/27 18:59:58 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_status	is_valid_args(char **args)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (!args)
		return (ft_printf_fd(2, RED "unset:" RESET " not enough arguments\n"),
			PTR_NULL);
	if (!*args)
		return (FAILED);
	while (args[++i])
	{
		while (ft_strlen(args[i]) < ++j)
		{
			if (ft_isspace(args[i][j]) == SUCCESS)
			{
				ft_printf_fd(2,
					RED "unset: " RESET "%s: " YELLOW "not a valid \
					identifier" RESET, args[i]);
				return (FAILED);
			}
		}
	}
	return (SUCCESS);
}

static t_status	delete_env(t_env *prev, t_env **current, t_env **envp)
{
	t_env	*tmp;

	tmp = NULL;
	if (!current)
		return (PTR_NULL);
	if (!prev)
	{
		tmp = *current;
		*current = (*current)->next;
		if (envp && *envp == tmp)
			*envp = *current;
		ft_free(2, &tmp->name, &tmp);
		return (SUCCESS);
	}
	else
	{
		prev->next = (*current)->next;
		ft_free(2, &(*current)->name, current);
		*current = prev;
		return (SUCCESS);
	}
}

static void check_envp(t_env **env, char **args)
{
	int i;
	t_env *tmp;
	t_env *prev;

	i = -1;
	while(args[++i])
	{
		prev = NULL;
		tmp = *env;
		while(tmp)
		{
			if (ft_strcmp(tmp->name, args[i]) == 0
				&& ft_strlen(tmp->name) == ft_strlen(args[i]))
				{
					delete_env(prev, &tmp, env);
					break;
				}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

t_status	unset(t_shell *sh, char **args)
{
	if (!sh)
		return (PTR_NULL);
	if (is_valid_args(args) != SUCCESS)
		return (FAILED);
	check_envp(&sh->envp, args);
	check_envp(&sh->user_env, args);
	return (SUCCESS);
}
