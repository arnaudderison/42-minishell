/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_new_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:05:02 by aderison          #+#    #+#             */
/*   Updated: 2024/12/20 15:43:43 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_new_var(t_shell *sh, char *name)
{
	t_env	*tmp;
	int		size;

	if (!name || !sh)
		return (false);
	size = ft_strlen(name);
	tmp = sh->envp;
	while (tmp)
	{
		if (ft_strlen(tmp->name) == size && ft_strcmp(name, tmp->name) == 0)
			return (false);
		tmp = tmp->next;
	}
	tmp = sh->user_env;
	while (tmp)
	{
		if (ft_strlen(tmp->name) == size && ft_strcmp(name, tmp->name) == 0)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
