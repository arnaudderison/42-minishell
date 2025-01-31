/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2025/01/31 02:56:30 by aderison         ###   ########.fr       */
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

void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = init_envp(envp);
	shell->user_env = NULL;
}

void	process_input(char *input, t_shell *shell)
{
	if (handle_eof(input, shell))
	{
		if (input && ft_strlen(input) < MAX_INPUT_LENGHT)
		{
			if (!handle_parsing(input, shell))
				return ;
		}
		ft_free(1, &input);
		cmds_path(shell);
		if (!shell->cmds[0])
			return ;
		shell->exit_code = execute_cmds(shell);
		free_cmd_array(shell->cmds, -1);
		ft_free_matrice(1, &shell->env_execve);
	}
}

void	cleanup(t_shell *shell, char *input)
{
	if (input)
		ft_free(1, &input);
	ft_free(1, &shell->envp);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_shell	shell;

	(void)argv;
	if (argc != 1)
		exit(EXIT_FAILURE);
	init_shell(&shell, envp);
	while (true)
	{
		setup_prompt_signals();
		input = readline(GREEN "minish ~ " RESET);
		process_input(input, &shell);
	}
	cleanup(&shell, input);
	return (0);
}
