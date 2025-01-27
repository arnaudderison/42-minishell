/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 01:41:06 by aderison          #+#    #+#             */
/*   Updated: 2025/01/27 19:04:07 by aderison         ###   ########.fr       */
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
		if(tmp->value)
			ft_printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			ft_printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
