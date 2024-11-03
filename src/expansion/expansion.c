/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:43:56 by aderison          #+#    #+#             */
/*   Updated: 2024/11/03 19:33:37 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 * 1 creer une liste des variables d'env 
 * 2 parcourir l'input et changer les valeurs en fonction des quote et dquotes
 * 
 * 
 * parcourir input
 * si !$
 *  join depuis une nouvelle chaine (le but est de reconstruire l'input)
 * si $
 *  recuperer le nom de la var (on ne prends pas en compte ? pour le moment)
 *      pour la recuperation du nom ce qui suit $ doit etre alphanum (ft_isalnum elle n'est pas encore faites)
 *      parcourir la list des env si on trouve le nom join sur le nouveau input avec la valeur de la $VAR
 * si  une quote est ouverte il faut ne faut pas prendre en compte les $Var (voir substr)
 * si une dquote est ouverte alors il faut gerer les $VAR

*/