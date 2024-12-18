/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name_later.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:08:12 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 13:08:48 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 10 && c <= 13))
		return (1);
	return (0);
}

int	is_oper(char c)
{
	if (c == '=' || c == '|' || c == ';')
		return (1);
	return (0);
}

int	ft_isend(const char c)
{
	if (ft_isspace(c) || c == '\'' || c == '\"' || c == '|' || c == ';')
		return (1);
	return (0);
}

char	*delete_space(char *command)
{
	int	i;

	i = ft_strlen(command) - 1;
	while (i >= 0 && ft_isspace(command[i]))
	{
		command[i] = '\0';
		i--;
	}
	return (command);
}

int	state_finish(t_token *token)
{
	return (token->nb_word);
}

char 	*delete_inutile_quote(char *command)
{
	int i;
	int prev_i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\'' || command[i] == '\"')
		{
			prev_i = i;
			i++;
			while (command[i] && (command[prev_i] != command[i]))
				i++;
			if (i - prev_i < 2 && command[prev_i + 1])
			{
				command[prev_i] = ' ';
				command[prev_i + 1] = ' ';
			}
		}
		i++;
	}
	return (command);
}

