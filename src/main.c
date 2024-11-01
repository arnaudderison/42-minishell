/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/11/01 19:09:46 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in waiting handle signals
void	handle_eof(char *line)
{
	if (line == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
}

int	main(void)
{
	char	*input;

	input = NULL;
	while (true)
	{
		input = readline(GREEN "minish ~ " RESET);
		handle_eof(input);
		if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
			tokeniser((const char *)input);
	}
	return (0);
}
