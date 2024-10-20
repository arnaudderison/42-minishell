/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/10/20 03:46:43 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	input = NULL;
	while (true)
	{
		ft_putstr_fd(GREEN "minish ~ " RESET, 1);
		input = get_next_line(0);
		input[ft_strlen(input) - 1] = '\0';
		if (input[0])
			tokeniser((const char *)input);
		ft_free(1, &input);
	}
	system("leaks ./minishell");
	return (0);
}
