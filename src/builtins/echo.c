/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:12:35 by aderison          #+#    #+#             */
/*   Updated: 2025/01/09 17:08:53 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_endl_echo(char **arg, int nb)
{
	if (!arg || !*arg)
		return (nb);
	if (ft_strncmp(*arg, "-n", 2) == 0)
		return (is_endl_echo(arg + 1, nb + 1));
	return (nb);
}

/*
 * The echo command writes its arguments separated by a space and terminates
 * -n: Do not print the trailing newline character.
 */
t_status	echo(char **args, int endl)
{
	int	i;

	if (!args || !*args)
		return (FAILED);
	i = endl - 1;
	while (args[++i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
	}
	if (endl == 0)
		ft_printf("\n");
	return (SUCCESS);
}
