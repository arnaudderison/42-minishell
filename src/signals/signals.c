/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:12:53 by plachard          #+#    #+#             */
/*   Updated: 2024/11/07 20:26:40 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

g_flag = 0;

void    sighandler(int signum, void (*handler)(int))
{
    struct sigaction    sa;
}
/*  gestion du signal   */
//interrompre cmd 
// reafficher le prompt