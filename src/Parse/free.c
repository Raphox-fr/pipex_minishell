/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:09:05 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 13:13:24 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/Parsing.h"

void	killer_split(t_split *split, int nb_split)
{
	int	itr;

	itr = 0;
	if (!split)
		return ;
	while (itr < nb_split)
	{
		free(split[itr].word);
		itr++;
	}
	free(split);
}

static void	killer_array(char **buff, const int len)
{
	int	itr;

	itr = 0;
	while (itr < len)
	{
		free(buff[itr]);
		itr++;
	}
}

void	killer_request(t_data_rule *request)
{
	int	k;
	int	nb_command;

	k = 0;
	if (!(request))
		return ;
	nb_command = request[0].nb_command;
	if (request[k].pipe)
	{
		while (k < nb_command)
		{
			free((request[k]).command);
			if (request[k].nbr_args != 0)
			{
				killer_array(request[k].arguments, request[k].nbr_args);
				free(request[k].arguments);
			}
			if (request[k].nb_rdir != 0)
			{
				killer_array(request[k].out, request[k].nb_rdir);
				free(request[k].oper);
			}
			k++;
		}
	}
	free(request);
}
