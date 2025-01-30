

t_status	access_cmd(t_cmd **cmd_tab)
{
	int	i;

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
		// printf("cmd[%d] path = %s\n", i, cmd_tab[i]->path);
		// Vérification de la validité de cmd et cmd[0]
		if (!cmd_tab[i]->cmd || !cmd_tab[i]->cmd[0])
		{
			printf("Error: cmd[%d] has no valid command structure.\n", i);
			return (FAILED);
		}
		// Vérification des permissions d'accès
		if (access(cmd_tab[i]->path, X_OK) != 0)
		{
			printf("Error: access denied for cmd_tab[%d]: %s\n", i,
				cmd_tab[i]->path);
			return (FAILED);
		}
	}
	return (SUCCESS);
}
