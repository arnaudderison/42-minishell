/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 19:14:26 by aderison          #+#    #+#             */
/*   Updated: 2024/11/03 19:18:04 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	free_env(t_env *env)
{
	if (!env)
		return (PTR_NULL);
	free_env(env->next);
	ft_free(3, &env->name, &env->value, &env);
	return (SUCCESS);
}
