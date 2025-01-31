/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plachard <plachard@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:21:27 by plachard          #+#    #+#             */
/*   Updated: 2025/01/31 01:48:28 by plachard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(t_token *token_lst)
{
	int	count;

	count = 0;
	if (!token_lst)
		return (0);
	while (token_lst)
	{
		if (token_lst->type == TOKEN_PIPE)
			++count;
		token_lst = token_lst->next;
	}
	return (count);
}

void	free_pipes(int **pipes, int n_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = -1;
	while (++i < n_pipes)
	{
		if (pipes[i])
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			ft_free(1, &pipes[i]);
		}
	}
	free(pipes);
	pipes = NULL;
}

void	set_pipes(t_cmd **cmds, int **pipes, int i)
{
	if (!cmds[i]->in && i != 0)
	{
		cmds[i]->in = (t_redir *)malloc(sizeof(t_redir));
		if (!cmds[i]->in)
			exit(1);
		cmds[i]->in->fd = pipes[i][0];
		cmds[i]->in->file = NULL;
	}
	if (!cmds[i]->out)
	{
		cmds[i]->out = (t_redir *)malloc(sizeof(t_redir));
		if (!cmds[i]->out)
			exit(1);
		if (i == (cmds_count(cmds) - 1))
			cmds[i]->out->fd = 1;
		else
			cmds[i]->out->fd = pipes[i + 1][1];
		cmds[i]->out->file = NULL;
	}
	return ;
}

int	**pipe_cmds(t_cmd **cmds)
{
	int	**pipes;
	int	i;
	int	n;

	n = cmds_count(cmds);
	pipes = malloc(sizeof(int *) * (n + 1));
	i = -1;
	while (++i < n + 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			exit(1);
		if (pipe(pipes[i]) < 0)
			exit(1);
	}
	i = -1;
	while (++i < n)
		set_pipes(cmds, pipes, i);
	return (pipes);
}

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}
