/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 20:59:16 by aderison          #+#    #+#             */
/*   Updated: 2024/12/26 21:02:53 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		i;

	new_str = malloc(ft_strlen(str) + 2);
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i])
		new_str[i] = str[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	ft_free(1, &str);
	return (new_str);
}

static char	*handle_quotes(char **new_str, const char *str, int *i, char *saved)
{
	char	*tmp;

	tmp = ft_strdup(*new_str);
	ft_free(1, new_str);
	(*i)++;
	while (str[*i] && str[*i] != '"' && str[*i] != '\'')
		(*i)++;
	if (str[*i])
	{
		*saved = 0;
		(*i)++;
	}
	return (tmp);
}

char	*clean_quote(const char *str)
{
	char	saved;
	int		i;
	char	*new_str;

	i = 0;
	saved = 0;
	new_str = ft_strdup("");
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && saved == str[i]
			&& str[i + 1] && (str[i + 1] == '"' || str[i + 1] == '\''))
			new_str = handle_quotes(&new_str, str, &i, &saved);
		else if (str[i] == '"' || str[i] == '\'')
		{
			if (saved == 0)
				saved = str[i];
			i++;
		}
		else
			new_str = ft_strjoin_char(new_str, str[i++]);
	}
	ft_free(1, &str);
	return (new_str);
}
