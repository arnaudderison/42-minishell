/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2025/01/30 22:46:33 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	handle_eof(char *line, t_shell *sh)
{
	char	c;

	(void)sh;
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
	if (!line)
	{
		ft_printf("exit\n");
		exit(0);
	}
	return (false);
}

int	main(int argc, char **argv, char **envp)
{
	char *input;
	t_shell shell;

	(void)argv;
	input = NULL;
	shell.envp = NULL;
	if (argc != 1)
		exit(EXIT_FAILURE);
	shell.envp = init_envp(envp);
	shell.user_env = NULL;
	while (true)
	{
		setup_prompt_signals();
		input = readline(GREEN "minish ~ " RESET);
		if (handle_eof(input, &shell) == 1)
		{
			if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
				if(!handle_parsing((const char *)input, &shell))
					continue;
			ft_free(1, &input);
			cmds_path(&shell);
			if (!shell.cmds[0])
				continue ;
			shell.exit_code = execute_cmds(&shell);
			free_cmd_array(shell.cmds, -1);
			ft_free_matrice(1, &shell.env_execve);
		}
		if(input)
			ft_free(1, &input);
	}
	ft_free(1, &shell.envp);
	return (0);
}
