/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/12/25 14:37:36 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	handle_eof(char *line, t_shell *shell)
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
		free_env(shell->envp);
		free_env(shell->user_env);
		exit(0);
	}
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;
	/*test*/
	char	**cmd;
	/*test*/

	(void)argv;
	input = NULL;
	shell.envp = NULL;
	shell.user_env = NULL;
	if (argc != 1)
		exit(EXIT_FAILURE);
	shell.envp = init_envp(envp);
	while (true)
	{
		setup_prompt_signals();
		input = readline(GREEN "minish ~ " RESET);
		if (handle_eof(input, &shell) == 1)
		{
			add_history(input);
			/*test*/
			cmd = ft_split(input, ' ');
			execb(cmd, &shell);
			ft_free_matrice(1, &cmd);
			/*test*/
			cmd = NULL; 
			if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
				handle_parsing((const char *)input, &shell);
		}
	}
	return (0);
}
