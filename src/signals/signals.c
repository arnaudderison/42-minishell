/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:12:53 by plachard          #+#    #+#             */
/*   Updated: 2024/12/25 14:05:09 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

void setup_prompt_signals()
{
    struct sigaction sa;

    sa.sa_handler = handle_sigint_prompt;
    sa.sa_flags = SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGQUIT, &sa, NULL);

}
    