/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:33:40 by aderison          #+#    #+#             */
/*   Updated: 2024/11/04 16:27:48 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *name, t_env *envp)
{
	t_env	*tmp;
	int		size;

	if (!name || !envp)
		return (NULL);
	size = ft_strlen(name);
	tmp = envp;
	while (tmp)
	{
		if (ft_strlen(tmp->name) == size && ft_strcmp(name, tmp->name) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
