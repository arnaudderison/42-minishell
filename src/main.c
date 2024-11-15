/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/29 20:03:57 by plachard         ###   ########.fr       */
=======
/*   Updated: 2024/11/06 16:45:27 by aderison         ###   ########.fr       */
>>>>>>> 7551c5383546870b865a58aa1c7c02ad98d8d579
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
volatile sig_atomic_t signal_flag = 0;

void	handle_signal(int signum)
{
	flag = 1;
}

 /* Signal vector "template" used in sigaction call.
struct  sigaction {
	union __sigaction_u __sigaction_u;  signal handler
	sigset_t sa_mask;               	signal mask to apply
	int     sa_flags;               	see signal options below
};*/
int main(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_signal; // associe signum et gestionnaire de signaux
	sigemptyset(&sa.sa_mask);		// pas d'autres signaux a bloquer
	sa.sa_flags = 0;				// pas de cptm specifiques
	sigaction(SIGTERM, &sa, NULL); 	// fonction signal : definir un gestionnaire pour asocier une action au signal donne
	while (1);
	return(0);

=======
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
		ft_printf("exit %s\n", envp->name);
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
		input = readline(GREEN "minish ~ " RESET);
		if (handle_eof(input, shell.envp) == 1)
		{
			add_history(input);
			if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
				handle_parsing((const char *)input, &shell);
		}
	}
	return (0);
>>>>>>> 7551c5383546870b865a58aa1c7c02ad98d8d579
}

// int	main(void)
// {
// 	char	*input;

// 	input = NULL;
// 	while (true)
// 	{
// 		ft_putstr_fd(GREEN "minish ~ " RESET, 1);
// 		input = get_next_line(0);
// 		input[ft_strlen(input) - 1] = '\0';
// 		if (input[0] && ft_strlen(input) < MAX_INPUT_LENGHT)
// 			tokeniser((const char *)input);
// 	}
// 	return (0);
// }


