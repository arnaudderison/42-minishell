
#include "minishell.h"


char	*cmd_path(t_cmd *cmd, char **env)
{
	int		i;
	char	*tmp;
	char	*path;

	if (!cmd)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		tmp = ft_strjoin(env[i], "/");
		if (!tmp)
			exit(1);
		path = ft_strjoin(tmp, cmd->cmd[0]);
		if (!path)
		{
			ft_free(1, 1, &tmp);
			exit(1);
		}
		if (access(path, X_OK) == 0)
			return (ft_free(1, 1, &tmp), path);
		ft_free(1, 2, &tmp, &path);
	}
	ft_printf(" command not found: %s\n", cmd->cmd[0]);
	return (NULL);
}

char	**all_path()
{
	char	*str_env;
	char	**env;
	char	*tmp;
	int		i;

	str_env = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin");
	if (!str_env)
		return (NULL);
	env = ft_split(str_env, ':');
	ft_free(1, &str_env);
	if (!env)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		tmp = ft_strjoin(env[i], "/");
		if (!tmp)
		{
			// Free les précédentes allocations en cas d'erreur
			while (i-- > 0)
				ft_free(1, &env[i]);
			ft_free(1, env);
			return (NULL);
		}
		ft_free(1, &env[i]);
		env[i] = tmp;
	}
	return (env);
}

t_status	set_path(t_cmd	*cmd, char	**env)
{
	int		i;

	i = -1;
	if (!cmd || !cmd->cmd || !cmd->cmd[0])
    	return (FAILED);
	while (env && env[++i])
	{
		cmd->path = ft_strjoin(env[i], cmd->cmd[0]);
		if (!cmd->path)
			return (FAILED);
		if (access(cmd->path, X_OK) == 0)
			return (SUCCESS);
		ft_free(1, &cmd->path);
	}
	ft_printf(" command not found: %s\n", cmd->cmd[0]);
	return (FAILED);
}

t_status    cmds_path(t_cmd **cmd_tab, char **env)
{
	int i = -1;
	
	printf("cmd path------------\n");
	while (cmd_tab[++i] && cmd_tab[i]->cmd)
	{
		printf("---------boucle cmd path [%d]\n", i);
		//printf("access cmd %s\n", cmd_tab[i]->cmd[0]);
		if (access(cmd_tab[i]->cmd[0], X_OK) == 0)
		{
			cmd_tab[i]->path = cmd_tab[i]->cmd[0];
			printf("END cmd path------------\n");
			return (SUCCESS);
		}
		else
		{
			printf("set path\n");
			if (set_path(cmd_tab[i], env))
			{
				printf("END cmd path------------\n");
				return (SUCCESS);
			}
		}	
	}
	return (FAILED);
}
 /*
// Vérifie si les commandes du tableau cmd_tab sont accessibles/exécutables.
// Retourne SUCCESS si toutes sont accessibles, sinon FAILED.
// si fail : print cmd non find ?
t_status access_cmd(t_cmd **cmd_tab)
{
    int i;

    i = -1;
    while (cmd_tab[++i])
    {
		if (!cmd_tab[i]->path)
			printf("no path for cmd %s\n", cmd_tab[i]->cmd[0]);
		printf("cmd[%d] path = %s\n", i, cmd_tab[i]->path);
        if (!cmd_tab[i]->path)
        {
            printf("No path defined for cmd_tab[%d]\n", i);
            return (FAILED);
        }
        if (!cmd_tab[i]->cmd || !cmd_tab[i]->cmd[0])
        {
            printf("Invalid command structure at index %d\n", i);
            return (FAILED);
        }
        if (access(cmd_tab[i]->path, X_OK) != 0)
        {
            printf("Access denied for cmd_tab[%d]: %s\n", i, cmd_tab[i]->path);
            return (FAILED);
        }
		printf("access cmd %s\n", cmd_tab[i]->cmd[0]);
    }
	printf("access cmd done\n");
    return (SUCCESS);
}
*/

t_status access_cmd(t_cmd **cmd_tab)
{
    int i;

    i = -1;
    while (cmd_tab[++i])
    {
        // Vérification de la validité du cmd_tab[i]
        if (!cmd_tab[i])
        {
            printf("Error: cmd_tab[%d] is NULL\n", i);
            return (FAILED);
        }

        // Vérification de la validité de cmd_tab[i]->path
        if (!cmd_tab[i]->path)
        {
            printf("Error: cmd_tab[%d] has no path defined\n", i);
            // Affichage de la commande pour aider à comprendre l'origine du problème
            if (cmd_tab[i]->cmd && cmd_tab[i]->cmd[0])
                printf("Command: %s\n", cmd_tab[i]->cmd[0]);
            else
                printf("Command is NULL or empty.\n");
            return (FAILED);
        }

        // Affichage du chemin pour débogage
        printf("cmd[%d] path = %s\n", i, cmd_tab[i]->path);

        // Vérification de la validité de cmd et cmd[0]
        if (!cmd_tab[i]->cmd || !cmd_tab[i]->cmd[0])
        {
            printf("Error: cmd[%d] has no valid command structure.\n", i);
            return (FAILED);
        }

        // Vérification des permissions d'accès
        if (access(cmd_tab[i]->path, X_OK) != 0)
        {
            printf("Error: access denied for cmd_tab[%d]: %s\n", i, cmd_tab[i]->path);
            return (FAILED);
        }

        // Message pour indiquer que l'accès a réussi
        printf("Access granted for cmd %s\n", cmd_tab[i]->cmd[0]);
    }

    printf("Access check for all commands done.\n");
    return (SUCCESS);
}
