/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/10/31 16:06:27 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// in wait handle signals
void    handle_eof(char *line)
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
		ft_putstr_fd(GREEN "minish ~ " RESET, 1);
		input = get_next_line(0);
		handle_eof(input);
		input[ft_strlen(input) - 1] = '\0';
		if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
			tokeniser((const char *)input);
	}
	return (0);
}
