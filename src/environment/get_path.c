/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:46:12 by aderison          #+#    #+#             */
/*   Updated: 2025/01/31 00:22:11 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(t_shell *sh)
{
    char *path;

    path = get_env("PATH", &sh->envp);
    if(!path)
        path = get_env("PATH", &sh->user_env);
    if(!path)
        return ("");
    return (path);
}
