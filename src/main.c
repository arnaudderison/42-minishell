/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2025/01/23 17:58:39 by aderison         ###   ########.fr       */
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

void print_tokens(t_token *tokens)
{
	t_token	*token_lst = NULL;

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
            printf("Token type: %d, value: %s\n", token_lst->type, token_lst->value);
        else
            printf("Token corrompu ou pointeur NULL\n");
        token_lst = token_lst->next;
    }
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*input;
// 	t_shell	shell;

// 	(void)argv;
// 	input = NULL;
// 	shell.envp = NULL;
// 	if (argc != 1)
// 		exit(EXIT_FAILURE);
// 	shell.envp = init_envp(envp);
// 	shell.user_env = NULL;
// 	while (true)
// 	{
// 		setup_prompt_signals();
// 		input = readline(GREEN "minish ~ " RESET);
// 		if (handle_eof(input, shell.envp) == 1)
// 		{
// 			add_history(input);
// 			if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
// 				handle_parsing((const char *)input, &shell);
// 		}
//         //free(input);
// 		char **env = all_path();
// 		cmds_path(shell.cmds, env);
// 		printf("Checking access to commands...\n");
// 		if(!execb(shell.cmds[0]->cmd, &shell))
// 		{
// 			if (access_cmd(shell.cmds))
// 			{
// 				printf("execute\n");
// 				execute_simple_cmd(shell.cmds[0]);
// 			}
// 			else
// 				printf("Access to commands failed.\n");
// 		}
// 	}
// 	return (0);
// }

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
	shell.user_env = NULL;
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
        free(input);
		char **env = all_path();
		// printf("all_path set\n");
		cmds_path(shell.cmds, env);
		// printf("Checking access to commands...\n");
		if(!execb(shell.cmds[0]->cmd, &shell))
		{
			// if (access_cmd(shell.cmds))
			// {
			// 	printf("execute\n\n");
				execute_cmds(shell.cmds);
			// }
			// else
			// 	printf("Access to commands failed.\n");
		}
	}
	return (0);
}