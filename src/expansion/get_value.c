/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arnaud <arnaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:04:46 by arnaud            #+#    #+#             */
/*   Updated: 2025/01/30 16:15:33 by arnaud           ###   ########.fr       */
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
