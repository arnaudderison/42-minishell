/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 20:29:50 by aderison          #+#    #+#             */
/*   Updated: 2024/12/26 21:08:24 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
	{
		ft_printf_fd(2,
			RED "export: " RESET "%s: " YELLOW "not a valid identifier" RESET,
			str);
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_printf_fd(2,
				RED "export: " RESET "%s: " YELLOW "not a valid identifier" RESET,
				str);
			return (0);
		}
		i++;
	}
	return (1);
}

static t_status	print_env(t_env *envp)
{
	t_env	*tmp;

	if (!envp)
		return (PTR_NULL);
	tmp = envp;
	while (tmp)
	{
		ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
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
				tmp_swap = *tmp;
				*tmp = *tmp2;
				*tmp2 = tmp_swap;
				tmp_swap.next = tmp2->next;
				tmp2->next = tmp->next;
				tmp->next = tmp_swap.next;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	print_env(start);
	return (SUCCESS);
}

// if an value of variable is null, it won't work
static t_status	export_variable(t_shell *sh, const char *arg, size_t argl)
{
	char	*equal_sign;
	char	*plus_equal_sign;
	char	*new_value;
	char	*value;
	char	*name;

	plus_equal_sign = ft_strnstr(arg, "+=", argl);
	equal_sign = ft_strnstr(arg, "=", argl);
	if (plus_equal_sign)
	{
		name = ft_substr(arg, 0, argl - ft_strlen(plus_equal_sign));
		if (is_new_var(sh, name))
			set_var_env(name, plus_equal_sign + 2, sh);
		else
		{
			value = get_env(name, &(sh->envp));
			if (!value)
				value = get_env(name, &(sh->user_env));
			new_value = ft_strjoin(value, plus_equal_sign + 2);
			if (!new_value)
				return (MALLOC);
			set_var_env(name, new_value, sh);
			ft_free(1, &new_value);
		}
		ft_free(1, &name);
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
