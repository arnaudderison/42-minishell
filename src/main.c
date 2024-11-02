/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/11/02 16:22:49 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	handle_eof(char *line)
{
	char c;

	if (line == NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	while (*line)
	{
		c = *line;
		if (c != ' ' && c != '\t')
			return (true);
		line++;
	}
	return (false);
}

int	main(void)
{
	char	*input;

	input = NULL;
	while (true)
	{
		input = readline(GREEN "minish ~ " RESET);
		if(handle_eof(input) == 1)
		{
			add_history(input);
			if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
				tokeniser((const char *)input);
		}	
	}
	return (0);
}
