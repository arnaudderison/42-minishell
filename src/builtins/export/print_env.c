/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 01:41:06 by aderison          #+#    #+#             */
/*   Updated: 2025/01/17 01:41:17 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

t_status	print_env(t_env *envp)
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

