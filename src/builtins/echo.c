/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:12:35 by aderison          #+#    #+#             */
/*   Updated: 2024/12/11 16:40:23 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_endl_echo(char *arg)
{
	if (ft_strcmp(arg, "-n") == 0 && ft_strlen(arg) == 2)
		return (true);
	return (false);
}

/*
 * The echo command writes its arguments separated by a space and terminates
 * -n: Do not print the trailing newline character.
 */
t_status	echo(char **args, t_bool endl)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
	}
	if (endl)
		ft_printf("\n");
	return (SUCCESS);
}
