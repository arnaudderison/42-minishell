/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 04:40:10 by aderison          #+#    #+#             */
/*   Updated: 2024/12/18 17:15:54 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	env(t_env *envp)
{
	t_env	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
