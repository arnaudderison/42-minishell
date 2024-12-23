/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/12/03 22:03:05 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	handle_eof(char *line, t_env *envp)
{
	char	c;

	if (line)
	{
		while (*line)
		{
			c = *line;
			if (c != ' ' && c != '\t')
				return (true);
			line++;
		}
	}
	if (line == NULL)
	{
		ft_printf("exit\n");
		free(envp->name);
		exit(0);
	}
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	(void)argv;
	input = NULL;
	shell.envp = NULL;
	if (argc != 1)
		exit(EXIT_FAILURE);
	shell.envp = init_envp(envp);
	while (true)
	{
		setup_prompt_signals();
		input = readline(GREEN "minish ~ " RESET);
		if (handle_eof(input, shell.envp) == 1)
		{
			add_history(input);
			if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
				handle_parsing((const char *)input, &shell);
		}
	}
	return (0);
}
