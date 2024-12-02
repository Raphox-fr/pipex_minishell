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

static int	find_size(char *buff, const int len, t_var **var)
{
	int i;
	int size;

	size = 0;
	i = 0;
	while (i < len)
	{
		if (buff[i] == '$' && var_exist(buff + i + 1, var))
		{
			printf("ca exist\n");
		}
		i++;
	}
	return (0);
}

static void	is_double_quote(t_split *split, char *command)
{
	split->word = ft_calloc(sizeof(char), split->len_word);
	if (!split->word)
		return ;
	ft_strlcpy(split->word, command, split->len_word);
}

static void	is_simple_quote(t_split *split, char *command, t_var **var)
{
	printf("size : %d\n", find_size(command, split->len_word, var));
}

void	add_quote(t_split *split, char *command, int *index, t_var **var)
{
	if (!command)
		return ;
	if (command[0] == command[1])
	{
		(*index) += 2;
		return ;
	}
	if (command[0] == '\'')
		is_simple_quote(split, command, var);
	else if (command[0] == '\"')
		is_double_quote(split, command);
	(*index)++;
}