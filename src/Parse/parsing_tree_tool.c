/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tree_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:25:22 by thodos-s          #+#    #+#             */
/*   Updated: 2024/12/05 12:46:21 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"
#include "../../includes/minishell.h"

int	node_finish(char *buff, int len)
{
	if (!buff || buff == NULL)
		return (1);
	if (ft_strncmp(buff, "|", len) == 0 || ft_strncmp(buff, ";", len) == 0 \
		|| check_rdir(buff, len) != OTHER)
		return (1);
	return (0);
}

int	check_rdir(char *buff, int len)
{
	if (ft_strncmp(buff, ">", len) == 0)
		return (RDIR);
	if (ft_strncmp(buff, "<", len) == 0)
		return (INPUT);
	if (ft_strncmp(buff, ">>", len) == 0)
		return (D_RDIR);
	if (ft_strncmp(buff, "<<", len) == 0)
		return (D_INPUT);
	if (ft_strncmp(buff, "|", len) == 0)
		return (PIPE);
	else
		return (OTHER);
}

int	r_node(t_split *split, int nb_node)
{
	int	node_type;

	node_type = 0;
	if (split[nb_node].word == NULL)
		return (nb_node);
	if (node_finish(split[nb_node].word, split[nb_node].len_word))
		return (nb_node);
	node_type = check_rdir(split->word, split->len_word);
	if (node_type == OTHER)
	{
		nb_node++;
		return (r_node(split, nb_node));
	}
	else if (node_type == RDIR || node_type == D_INPUT || node_type == PIPE)
		return (r_node(split, nb_node));
	return (-1);
}

int	ft_nbr_option(const t_split *split, const int nb_node)
{
	int	nb_opt;
	int	i;

	i = 0;
	nb_opt = 0;
	if (!split)
		return (0);
	while (i < nb_node - 1)
	{
		if (split[i].word[0] == '-')
			nb_opt++;
		if (split[i].word[0] != '-')
			break ;
		i++;
	}
	return (nb_opt);
}

int	ft_nb_rdir(t_split *split)
{
	int	itr;
	int	rdir;
	int	nb_rdir;

	itr = 0;
	nb_rdir = 0;
	while (split[itr].word != NULL
		&& ft_strncmp(split[itr].word, "|", split[itr].len_word) != 0)
	{
		rdir = check_rdir(split[itr].word, split[itr].len_word);
		if (rdir != OTHER && rdir != PIPE)
			nb_rdir++;
		itr++;
	}
	return (nb_rdir);
}
