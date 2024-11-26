/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:04:30 by umbra             #+#    #+#             */
/*   Updated: 2024/11/20 15:19:01 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"
#include "Parsing.h"

static	int	converte_rdir(t_data_rule *request, t_split *split)
{
	int	rdir;
	int	itr;
	int	itr_oper;

	itr = 0;
	itr_oper = 0;
	request->nb_rdir = ft_nb_rdir(split);
	request->oper = ft_calloc(sizeof(char *), request->nb_rdir + 1);
	if (!request->oper)
		return (-1);
	while (split[itr].word != NULL
		&& node_finish(split[itr].word, split[itr].len_word))
	{
		rdir = check_rdir(split[itr].word, split->len_word);
		if (rdir != OTHER && rdir != PIPE)
		{
			fill_conv_rdir(request, rdir, itr_oper);
			itr_oper++;
		}
		itr++;
	}
	return (request->nb_rdir);
}

static int	fill_request(t_split *split, t_data_rule *request, \
			int count_word, int k)
{
	int	nb_node;
	int	nb_opt;

	nb_node = 0;
	if (count_word <= 0)
		return (0);
	nb_node = r_node(split, 0);
	if (nb_node == -1)
		return (-1);
	add_command(&request[k], split);
	nb_opt = ft_nbr_option(split + 1, nb_node);
	if (nb_opt)
		add_opt_request(&request[k], split + 1, nb_opt);
	request[k].pipe = false;
	if (nb_node > 1 + nb_opt)
		request[k].nbr_args = add_arg_request(&request[k], \
				split + nb_opt + 1, nb_opt, nb_node);
	if (count_word > nb_node && converte_rdir(&request[k], &split[nb_node]))
		nb_node += add_rdir(&request[k], split + nb_node);
	if (nb_node < count_word)
		nb_node += add_pipe(&request[k], split + nb_node, count_word);
	if (nb_node < count_word)
		nb_node += add_semicolon(split + nb_node);
	count_word -= nb_node;
	return (fill_request(split + nb_node, request, count_word, k + 1));
}

t_data_rule	*parsing_tree(t_split *split, const int count_word)
{
	t_data_rule	*out;

	out = ft_calloc(sizeof(t_data_rule), nb_command(split, count_word));
	if (!out)
		return (NULL);
	out->nb_command = nb_command(split, count_word);
	out->nbr_args = 0;
	if (fill_request(split, out, count_word, 0) == -1)
	{
		free(out);
		return (NULL);
	}
	return (out);
}
