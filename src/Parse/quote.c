/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:33:22 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 15:37:19 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/Parsing.h"

static int	find_var_in_quote(const char *buff, int len)
{
	int				i;
	unsigned int	var_count;

	i = 0;
	var_count = 0;
	while (i < len)
	{
		if (buff[i] == '$')
			var_count++;
		i++;
	}
	return (var_count);
}

static void	is_double_quote(t_split *split, char *command)
{
	split->word = ft_calloc(sizeof(char), split->len_word);
	if (!split->word)
		return ;
	ft_strlcpy(split->word, command, split->len_word);
}

static void	is_simple_quote(t_split *split, char *command)
{
	split->word = ft_calloc(sizeof(char), split->len_word);
	if (!split->word)
		return ;
	ft_strlcpy(split->word, command, split->len_word);
}

void	add_quote(t_split *split, char *command)
{
	if (!command)
		return ;
	if (command[0] == '\'')
		is_simple_quote(split, command);
	else if (command[0] == '\"')
		is_double_quote(split, command);
}