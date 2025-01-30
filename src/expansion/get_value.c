/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:04:46 by arnaud            #+#    #+#             */
/*   Updated: 2025/01/30 23:00:20 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *name, t_shell *sh)
{
	char	*value;

	value = get_env(name, &sh->envp);
	if (!value)
		value = get_env(name, &sh->user_env);
	if (!value)
		value = "";
	return (value);
}
