/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 20:32:33 by aderison          #+#    #+#             */
/*   Updated: 2024/12/02 20:23:10 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


