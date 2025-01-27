/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:46:12 by aderison          #+#    #+#             */
/*   Updated: 2025/01/24 23:13:24 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_path(t_shell *sh)
{
    char *path;

    path = get_env("PATH", &sh->envp);
    if(!path)
        return (ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:\
    /usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin"));
    return (path);
}
