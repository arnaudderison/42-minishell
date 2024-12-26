/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:00:31 by aderison          #+#    #+#             */
/*   Updated: 2024/12/26 21:00:24 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer	*create_lexer(const char *input)
{
	t_lexer	*lexer;

	lexer = NULL;
	if (!input)
	{
		print_error(ERR_NULL_PTR, "tokeniser.c", 22);
		exit(EXIT_FAILURE);
	}
	lexer = malloc(sizeof(t_lexer));
	if (!lexer)
	{
		print_error(ERR_MALLOC, "tokeniser.c", 28);
		ft_free(1, &input);
		exit(EXIT_FAILURE);
	}
	lexer->input = input;
	ft_printf("NEW INPUT: [%s]\n", input);
	lexer->position = 0;
	lexer->last_token = NULL;
	return (lexer);
}

static void	init_tokens(t_token *tokens, t_shell *sh)
{
	tokens->type = NAO;
	tokens->next = NULL;
	tokens->value = NULL;
	sh->tokens = tokens;
}
// static char *ft_strjoin_char(char *str, char c)
// {
//    char *new_str;
//    int i;

//    new_str = malloc(ft_strlen(str) + 2);
//    if (!new_str)
//        return (NULL);
//    i = -1;
//    while (str[++i])
//        new_str[i] = str[i];
//    new_str[i] = c;
//    new_str[i + 1] = '\0';
//    ft_free(1, &str);
//    return (new_str);
// }

// static char *clean_quote_str(const char *str)
// {
//    char saved;
//    int i;
//    char *new_str;
//    char *tmp;

//    i = 0;
//    saved = 0;
//    new_str = ft_strdup("");
//    while (str[i])
//    {
//        if ((str[i] == '"' || str[i] == '\'') && saved == str[i] && 
//            str[i + 1] && (str[i + 1] == '"' || str[i + 1] == '\''))
//        {
//            tmp = ft_strdup(new_str);
//            ft_free(1, &new_str);
//            i++;
//            while (str[i] && str[i] != '"' && str[i] != '\'')
//                i++;
//            if (str[i])
//            {
//                saved = 0;
//                i++;
//            }
//            new_str = tmp;
//        }
//        else
//        {
//            if (str[i] == '"' || str[i] == '\'')
//            {
//                if (saved == 0)
//                    saved = str[i];
//                i++;
//            }
//            else
//            {
//                new_str = ft_strjoin_char(new_str, str[i]);
//                i++;
//            }
//        }
//    }
//    ft_free(1, &str);
//    return new_str;
// }



t_bool	handle_parsing(const char *input, t_shell *sh)
{
	t_lexer	*lexer;
	t_token	*tokens;

	lexer = NULL;
	tokens = NULL;
	if (!input)
		exit(EXIT_FAILURE);
	lexer = create_lexer((const char *)clean_quote(expand_input((char *)input, sh->envp)));
	tokens = malloc(sizeof(t_token));
	if (!tokens)
		return (free_env(sh->envp), ft_free(2, &lexer), exit(EXIT_FAILURE),
			false);
	init_tokens(tokens, sh);
	create_tokenisation(&(sh->tokens), lexer);
	manage_quote(&(sh->tokens));
	parsing(sh->tokens);
	//print_tokens(sh->tokens);
    tokens_to_cmd(sh);
	printf("kdcxqjskhxl<bchbqch\n");
	if(!(sh->cmds))
	 	return (false);
	//return (free_tokens(sh->tokens, NULL), ft_free(2, &(lexer->input), &lexer), true);
	printf("kdcxqjskhxl<bchbqch\n");
	return (true);
}
