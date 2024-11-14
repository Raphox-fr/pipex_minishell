/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umbra <umbra@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:04:30 by umbra             #+#    #+#             */
/*   Updated: 2024/10/07 15:05:34 by umbra            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by umbra on 10/1/24.
//

#include "../../includes/Parsing.h"
#include "Parsing.h"

static int add_command(t_data_rule *request, t_split *split)
{
	if (!split)
		return (-1);
	request->command = split[0].word;
	return (0);
}

static int add_pipe(t_data_rule *request, t_split *split, int count_word)
{
	if (count_word <= 0 || !split)
		return (0);
	if (split->word && ft_strncmp(split->word, "|", split->len_word) == 0)
	{
		request->pipe = true;
		return (1);
	}
	return (0);
}

static int add_opt_request(t_data_rule *request, t_split *split, const int nb_opt)
{
	int i;

	i = 0;
	request->options = ft_calloc(sizeof(char *), nb_opt + 1);
	if (!request->options)
		return (-1);
	while (i < nb_opt)
	{
		request->options[i] = split[i].word;
		i++;
	}
	return (1);
}

static int	converte_rdir(t_data_rule *request, t_split *split)
{
	int rdir;
	int	itr;
	int itr_oper;
	int nb_rdir;

	itr = 0;
	itr_oper = 0;
	nb_rdir = 0;
	while (split[itr].word != NULL && ft_strncmp(split[itr].word, "|", split[itr].len_word) != 0)
	{
		rdir = check_rdir(split[itr].word, split[itr].len_word);
		if (rdir != OTHER && rdir != PIPE)
			nb_rdir++;
		itr++;
	}
	request->nb_rdir = nb_rdir;
	request->oper = ft_calloc(sizeof(char *), nb_rdir + 1);
	if (!request->oper)
		return (-1);
	itr = 0;
	while (split[itr].word != NULL && ft_strncmp(split[itr].word, "|", split[itr].len_word))
	{
		rdir = check_rdir(split[itr].word, split->len_word);
		if (rdir != OTHER && rdir != PIPE)
		{
			if (rdir == D_RDIR)
				request->oper[itr_oper] = 'r';
			if (rdir == RDIR)
				request->oper[itr_oper] = '>';
			if (rdir == INPUT)
				request->oper[itr_oper] = '<';
			itr_oper++;
		}
		itr++;
	}
	return (nb_rdir);
}

static int fill_request(t_split *split, t_data_rule *request, int count_word, int k)
{
	int nb_node;
	int nb_opt;

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
		request[k].nbr_args = add_arg_request(&request[k], split + nb_opt + 1, nb_node);
	if (count_word > nb_node && converte_rdir(&request[k], &split[nb_node]))
		nb_node += add_rdir(&request[k], split + nb_node, count_word);
	if ( nb_node < count_word)
		nb_node += add_pipe(&request[k], split + nb_node, count_word);
	count_word -= nb_node;
	return (fill_request(split + nb_node, request, count_word, k + 1));
}

t_data_rule		*parsing_tree(t_split *split, const int count_word)
{
	t_data_rule *out;
	int k = 0;

	out = ft_calloc(sizeof(t_data_rule), nb_command(split, count_word));
	if (!out)
		return (NULL);
	out->nb_command = nb_command(split, count_word);
	out->nbr_args = 0;
	if (fill_request(split, &out[k], count_word, 0) == -1) {
		free(out);
		return NULL;
	}
	return (out);
}