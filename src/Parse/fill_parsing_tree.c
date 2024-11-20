/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parsing_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:25:52 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 13:05:52 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by umbra on 11/12/24

#include "../../includes/minishell.h"
#include "../../includes/Parsing.h"

int	add_semicolon(t_split *split)
{
	if (split->word && ft_strncmp(split->word, ";", split->len_word) == 0)
		return (1);
	return (0);
}

int	add_arg_request(t_data_rule *request, t_split *split, int nb_node)
{
	int	itr_arg;

	itr_arg = 0;
	if (!split)
		return (-1);
	request->arguments = ft_calloc(sizeof(char *), nb_node + 1);
	while (itr_arg < nb_node - 1)
	{
		request->arguments[itr_arg] = split[itr_arg].word;
		itr_arg++;
	}
	return (itr_arg);
}

int	add_rdir(t_data_rule *request, t_split *split)
{
	int	rdir;
	int	itr_oper;
	int	itr;

	itr_oper = 0;
	itr = 0;
	if (!split)
		return (0);
	request->out = ft_calloc(sizeof(char *), request->nb_rdir + 1);
	if (!request->out)
		return (0);
	while (split[itr].word != NULL
		&& node_finish(split[itr].word, split[itr].len_word))
	{
		rdir = check_rdir(split[itr].word, split[itr].len_word);
		if (rdir != PIPE && rdir != OTHER)
		{
			fill_rdir(request, split, itr, itr_oper);
			itr++;
			itr_oper++;
		}
		itr++;
	}
	return (itr);
}
