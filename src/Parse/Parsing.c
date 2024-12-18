/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:13:38 by thodos-s          #+#    #+#             */
/*   Updated: 2024/12/05 12:47:24 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"
#include "../../includes/parsing_error.h"

int	ft_strnchr(char *str, char to_find, const int len)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (i < len)
	{
		if (str[i] == to_find)
			return (i);
		i++;
	}
	return (-1);
}

int	add_word(t_split *word, char *command, int *index)
{
	if (!command)
		return (0);
	word->word = ft_calloc(sizeof(char), word->len_word + 1);
	if (!word->word)
		return (-1);
	ft_strlcpy((word->word), command, word->len_word + 1);
	(*index)++;
	return (1);
}

static int	fill_info(char *command, int *word, t_var **var, t_split *split)
{
	int k;
	int i;
	int itr_word;
	int len_word;

	k = 0;
	i = 0;
	itr_word = 0;
	while (itr_word < *word)
	{
		while (ft_isspace(command[i]))
			i++;
		len_word = len_of_word(command, i);
		split[k].len_word = len_word;
		if (command[i] == '\"' || command[i] == '\'')
			add_quote(&split[k], command + i, &k, var);
		else
			add_word(&split[k], command + i, &k);
		i = len_word + i;
		itr_word++;
	}
	*word = k;
	return (0);
}

t_data_rule	*parsing(char *command, t_var **var, t_erreur *err)
{
	t_data_rule		*request;
	t_split			*split;
	int				word_count;

	split = NULL;
	request = NULL;
	command = delete_inutile_quote(command);
	command = delete_space(command);
	command = var_traitment(command, var);
	if (ft_strlen(command) == 0)
		return (NULL);
	word_count = nb_words(command);
	err->error_code = STX_NL;
	if (word_count < 0 || braquet_check(command, err) == -1)
		return (NULL);
	err->error_code = STX_ALLOC;
	split = ft_calloc(sizeof(t_split), ((word_count)) + 1);
	if (!split || (fill_info(command, &word_count , var, split) < 0))
		return (NULL);
	err->error_code = STX_NL;
	if (syntax_check(split, word_count, err))
		return (NULL);
	err->error_code = -1;
	request = parsing_tree(split, word_count);
	return (request);
}
