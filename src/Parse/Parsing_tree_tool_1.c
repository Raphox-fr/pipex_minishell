/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing_tree_tool_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:24:22 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 15:25:01 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

int	add_command(t_data_rule *request, t_split *split)
{
	if (!split)
		return (-1);
	request->command = split[0].word;
	return (0);
}

int	add_pipe(t_data_rule *request, t_split *split, const int count_word)
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

int	add_opt_request(t_data_rule *request,
			t_split *split, const int nb_opt)
{
	int	i;

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
