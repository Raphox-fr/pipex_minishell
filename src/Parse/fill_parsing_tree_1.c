/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_parsing_tree_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:07:05 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 13:07:58 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

static int	add_input_request(t_data_rule *request, t_split *split)
{
	if (!split)
		return (0);
	request->input = ft_strdup(split->word);
	return (1);
}

static int	add_out_request(t_data_rule *request, t_split *split, int itr_oper)
{
	if (split->word != NULL)
	{
		request->out[itr_oper] = ft_strdup(split->word);
		return (2);
	}
	return (0);
}

void	fill_rdir(t_data_rule *request, t_split *split, int itr, int itr_oper)
{
	if ((request->oper[itr_oper]) == '<' || request->oper[itr_oper] == 'h')
	{
		itr++;
		add_input_request(request, split + itr);
		add_out_request(request, split + itr, itr_oper);
	}
	else if ((request->oper[itr_oper] == '>'
			|| request->oper[itr_oper] == 'r'))
	{
		itr++;
		add_out_request(request, split + itr, itr_oper);
	}
}
