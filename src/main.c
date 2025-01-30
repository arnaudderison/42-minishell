/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2025/01/30 21:15:41 by aderison         ###   ########.fr       */
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
		// // free(envp->name);
		// if(sh->envp)
		// 	free_env(sh->envp);
		// if(sh->user_env)
		// 	free_env(sh->user_env);
		// if(sh->path)
		// 	ft_free(1, &sh->path);
		// if(sh->env_execve)
		// 	ft_free_matrice(1, &sh->env_execve);
		exit(0);
	}
	return (false);
}

void	print_tokens(t_token *tokens)
{
	t_token	*token_lst;

	token_lst = NULL;
	token_lst = tokens;
	printf("Liste des tokens :\n");
	if (!token_lst)
	{
		printf("NULLité\n");
		return ;
	}
	while (token_lst)
	{
		if (token_lst) // Vérifiez si le pointeur n'est pas NULL
			printf("Token type: %d, value: %s\n", token_lst->type,
				token_lst->value);
		else
			printf("Token corrompu ou pointeur NULL\n");
		token_lst = token_lst->next;
	}
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