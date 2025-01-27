/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:29:50 by aderison          #+#    #+#             */
/*   Updated: 2025/01/24 22:00:34 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	swap(t_env tmp_swap, t_env *tmp, t_env *tmp2)
{
	tmp_swap = *tmp;
	*tmp = *tmp2;
	*tmp2 = tmp_swap;
	return (tmp_swap);
}

static t_status	print_sorted_env(t_env **envp)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*start;
	t_env	tmp_swap;

	tmp = *envp;
	start = *envp;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2 && tmp2 != tmp)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
			{
				tmp_swap = swap(*tmp, tmp, tmp2);
				tmp_swap.next = tmp2->next;
				tmp2->next = tmp->next;
				tmp->next = tmp_swap.next;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (print_env(start));
}

static t_status	process_equal_sign(t_shell *sh, char *name, char *value)
{
	char	*getenv;
	char	*new_value;

	getenv = NULL;
	if (is_new_var(sh, name))
		set_var_env(name, value, sh);
	else
	{
		getenv = get_env(name, &(sh->envp));
		if (!getenv)
			getenv = get_env(name, &(sh->user_env));
		new_value = ft_strjoin(getenv, value);
		if (!new_value)
			return (MALLOC);
		set_var_env(name, new_value, sh);
		ft_free(1, &new_value);
	}
	// ft_free(1, &getenv);
	return (SUCCESS);
}
// if an value of variable is null, it won't work
static t_status	export_variable(t_shell *sh, const char *arg, size_t argl)
{
	char	*equal_sign;
	char	*plus_equal_sign;
	char	*name;

	plus_equal_sign = ft_strnstr(arg, "+=", argl);
	equal_sign = ft_strnstr(arg, "=", argl);
	if (plus_equal_sign)
	{
		name = ft_substr(arg, 0, argl - ft_strlen(plus_equal_sign));
		process_equal_sign(sh, name, equal_sign + 1);
	}
	else if (equal_sign)
	{
		name = ft_substr(arg, 0, equal_sign - arg);
		if (is_valid_identifier(name))
			set_var_env(name, equal_sign + 1, sh);
		ft_free(1, &name);
	}
	else
		set_var_env((char *)arg, NULL, sh);
	return (SUCCESS);
}

t_status	export(t_shell *shell, char **args)
{
	int	i;

	if (!args || !shell)
		return (PTR_NULL);
	if (!args[0])
	{
		print_sorted_env(&shell->envp);
		print_sorted_env(&shell->user_env);
		return (SUCCESS);
	}
	i = 0;
	while (args[i])
	{
		export_variable(shell, args[i], ft_strlen(args[i]));
		i++;
	}
	return (SUCCESS);
}
