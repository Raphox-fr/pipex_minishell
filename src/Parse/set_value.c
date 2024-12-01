/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:37:39 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 15:39:07 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

static int	is_d_quote(char *command, int i, t_token *token)
{
	int	k;

	k = i;
	while (command[i] && command[i] != '\"')
		i++;
	if (command[i] == '\"')
	{
		if (token->len_word == 0)
			token->len_word = i - k + 2;
		return (r_value(command, i + 1, token));
	}
	return (-1);
}

static int	is_quote(char *command, int i, t_token *token)
{
	int	k;

	k = i;
	while (command[i] && command[i] != '\'')
		i++;
	if (command[i] == '\'')
	{
		if (token->len_word == 0)
			token->len_word = i - k + 2;
		return (r_value(command, i + 1, token));
	}
	return (-1);
}

static int	is_r_oper(char *command, int i, t_token *token)
{
	int k;

	k = i;
	while (command[i] && is_oper(command[i]))
		i++;
	if (token->len_word == 0)
		token->len_word = i - k;
	return (r_value(command, i, token));
}

static int	is_space(char *command, int i, t_token *token)
{
	int	k;

	k = i;
	while (command[i] && !ft_isend(command[i]))
		i++;
	if (token->len_word == 0)
		token->len_word = i - k;
	return (r_value(command, i, token));
}

int	r_value(char *command, int i, t_token *token)
{
	int	l;

	l = ft_strlen(command);
	if (token->len_word > 0)
		return (token->len_word);
	if (i >= l)
		return (state_finish(token));
	while (ft_isspace(command[i]))
		i++;
	if (command[i] == '\0')
		return (state_finish(token));
	token->sep = command[i];
	token->state = state_in_view(command, i);
	(token->nb_word)++;
	if (token->state == SPACES)
		return (is_space(command, i, token));
	else if (token->state == QUOTE)
		return (is_quote(command, i + 1, token));
	else if (token->state == D_QUOTE)
		return (is_d_quote(command, i + 1, token));
	else
		return (is_r_oper(command, i, token));
}
