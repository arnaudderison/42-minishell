/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:35:20 by aderison          #+#    #+#             */
/*   Updated: 2025/01/27 18:21:29 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int len(char **cmd)
{
    int i;

    i = 0;
    while(cmd[i])
        i++;
    return (i);
}

static t_bool is_number(char *value)
{
    int i;

    i = 0; 
    if(!value)
        return (false);
    while(value[i])
    {
        if(!ft_isdigit(value[i]))
            return (false);
        ++i;
    }
    return (true);
}

void exitb(char **cmd)
{
    int exit_code;

    ft_printf("exit\n");
    if(!cmd || !cmd[0])
        exit(1);
    if(len(cmd) > 1)
    {
        ft_printf_fd(2, "minish: exit: too many arguments\n");
        return ;
    }
    if(!is_number(cmd[0]))
    {
        ft_printf_fd(2,"minish: exit: %s: numeric argument required\n", cmd[0]);
        exit(2);
    }
    else
    {
        exit_code = ft_atoi(cmd[0]) % 256;
        if (exit_code < 0)
            exit_code += 256;
        exit(exit_code);
    }
}
