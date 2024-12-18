/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:29:50 by aderison          #+#    #+#             */
/*   Updated: 2024/12/18 17:10:07 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static t_status	print_env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static t_status	print_sorted_env(t_env *envp)
{
	t_env	*tmp;
	t_env	*tmp2;
	t_env	*start;
	t_env	tmp_swap;

	tmp = envp;
	start = envp;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp->name, tmp2->name) > 0)
			{
				tmp_swap = *tmp;
				*tmp = *tmp2;
				*tmp2 = tmp_swap;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	print_env(start);
	return (SUCCESS);
}

// if an value of variable is null, it won't work
static t_status	export_variable(t_shell *sh, const char *arg)
{
	char	*equal_sign;
	char	*plus_equal_sign;
	char	*new_value;
	char	*value;

	plus_equal_sign = ft_strnstr(arg, "+=", ft_strlen(arg));
	equal_sign = ft_strnstr(arg, "=", ft_strlen(arg));
	if (plus_equal_sign)
	{
		if (is_new_var(sh, plus_equal_sign - arg))
			set_var_env(plus_equal_sign - arg, plus_equal_sign + 2, sh);
		else
		{
			value = get_env(plus_equal_sign - arg, sh->envp);
			if (!value)
				value = get_env(plus_equal_sign - arg, sh->user_env);
			ft_strlcpy(new_value, value, ft_strlen(value) + 1);
			ft_strlcat(new_value, value, ft_strlen(value) + 1);
			set_var_env(plus_equal_sign - arg, new_value, sh);
		}
	}
	else if (equal_sign)
		set_var_env(equal_sign - arg, equal_sign + 1, sh);
	else
		set_var_env(arg, NULL, sh);
}

t_status	export(t_shell *shell, char **args)
{
	int	i;

	if (!args || !shell)
		return (PTR_NULL);
	if (!args[1])
	{
		print_sorted_env(shell->envp);
		print_sorted_env(shell->user_env);
		return (SUCCESS);
	}
	i = 0;
	while (args[i])
	{
		export_variable(env, args[i]);
		i++;
	}
	return (SUCCESS);
}
