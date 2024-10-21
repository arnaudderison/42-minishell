/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/10/21 20:16:18 by aderison         ###   ########.fr       */
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
		if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
			tokeniser((const char *)input);
		ft_free(1, &input);
	}
	system("leaks ./minishell");
	return (0);
}
