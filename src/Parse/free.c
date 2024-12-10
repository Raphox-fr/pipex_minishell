/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:09:05 by thodos-s          #+#    #+#             */
/*   Updated: 2024/12/05 12:47:57 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../includes/Parsing.h"

void	free_var(t_var *var)
{
	t_var	*temp;

	temp = NULL;
	if (var == NULL)
		return ;
	while (var != NULL)
	{
		temp = var;
		var = var->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
}

void killer_split(t_split *split, const int nb_word)
{
	int i;

	i = 0;
	while (i <= nb_word)
		free(split[i++].word);
	free(split);
}

static void	killer_array(char **buff, const int len)
{
	int	itr;

	itr = 0;
	(void)len;
	while (itr < len)
	{
		free(buff[itr]);
		itr++;
	}
	free(buff);
	buff = NULL;
}

void	killer_request(t_data_rule *request)
{
	int	k;
	int	nb_command;

	k = 0;
	if (!(request))
		return ;
	nb_command = request[0].nb_command;
	while (k < nb_command)
	{
		free(request[k].command);
		if (request[k].nbr_args > 0)
			killer_array(request[k].arguments, request[k].nbr_args);
		if (request[k].nb_rdir > 0)
		{
			killer_array(request[k].out, request[k].nb_rdir);
			free(request[k].oper);
		}
		if (request[k].nb_opt > 0)
			killer_array(request[k].options, request[k].nb_opt);
		k++;
	}
	free(request);
}
