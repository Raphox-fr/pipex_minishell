/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:13:38 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 14:15:40 by thodos-s         ###   ########.fr       */
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

void	add_word(t_split *word, char *command, const int word_len)
{
	word->word = ft_calloc(sizeof(char), word_len + 1);
	if (!word->word)
		return ;
	ft_strlcpy(word->word, command, word_len + 1);
}

static int	fill_info(char *command, int word, t_split *split)
{
	int		k;
	int		i;
	int		itr_word;

	k = 0;
	i = 0;
	itr_word = 0;
	while (itr_word < word)
	{
		while (ft_isspace(command[i]))
			i++;
		split[k].len_word = len_of_word(command, i);
		if (command[i] == '\"' || command[i] == '\'')
			add_quote(&split[k], command + i);
		else
			add_word(&split[k], command + i, split[k].len_word);
		i = split[k].len_word + i;
		k++;
		itr_word++;
	}
	return (0);
}

t_data_rule	*parsing(char *command, t_erreur *err)
{
	t_data_rule		*request;
	t_split			*split;
	int				word_count;
	int				nb_var;

	split = NULL;
	command = delete_space(command);
	if (ft_strlen(command) == 0)
		return (NULL);
	word_count = nb_words(command);
	nb_var = find_var(command);
	err->error_code = STX_NL;
	if (word_count < 0 || braquet_check(command, err) == -1)
		return (NULL);
	err->error_code = STX_ALLOC;
	split = ft_calloc(sizeof(t_split), ((word_count - nb_var) + 2));
	if (!split || (fill_info(command, word_count, split) < 0))
		return (NULL);
	err->error_code = STX_NL;
	if (syntax_check(split, word_count - nb_var, err))
		return (NULL);
	request = parsing_tree(split, word_count - nb_var);
	return (request);
}
