/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_syntax.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:41:26 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 12:22:55 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/Parsing.h"

static int	occ_quote(char *buff)
{
	int	i;

	i = 0;
	while (buff[i] == '>' || buff[i] == '<')
		i++;
	return (i);
}

static int	quote_check(char *word, t_erreur *err, int i, const int nb_word)
{
	err->c = word[0];
	if ((ft_strlen(word) <= 2))
	{
		if (err->sw)
		{
			err->error_code = SYNTAX;
			return (-1);
		}
		else if ((((i == 0) && nb_word != 1)
				|| (i + 1) == nb_word) && !(err->sw))
		{
			err->error_code = STX_NL;
			return (-1);
		}
	}
	else if (occ_quote(word) > 2)
	{
		err->error_code = D_SYNTAX;
		return (-1);
	}
	return (0);
}

int	braquet_check(char *str, t_erreur *err)
{
	int	b_left;
	int	b_right;
	int	i;

	b_left = 0;
	b_right = 0;
	i = 0;
	err->error_code = SYNTAX;
	err->c = ')';
	while (str[i])
	{
		if (str[i] == '(' && empty_braquet(str + i))
			return (-1);
		if (str[i] == '(')
			b_left++;
		if (str[i] == ')')
			b_right++;
		i++;
	}
	if (b_left != b_right)
		return (-1);
	return (0);
}

int	oper_check(t_erreur *err, char sep, const int i, const int nb_word)
{
	err->c = sep;
	err->error_code = SYNTAX;
	if (err->sw)
	{
		err->error_code = D_SYNTAX;
		return (-1);
	}
	if (err->sw || i == 0 || (nb_word - 1) == i)
		return (-1);
	return (0);
}

int	syntax_check(t_split *split, const int nb_word, t_erreur *err)
{
	int			i;
	char		sep;

	i = 0;
	err->sw = 0;
	while (i < nb_word)
	{
		sep = split[i].word[0];
		if (sep == '|' || sep == ';' || sep == '<' || sep == '>' || sep == '&')
		{
			if (sep == '|' || sep == ';' || sep == '&')
			{
				if (oper_check(err, sep, i, nb_word) == -1)
					return (-1);
			}
			else if (sep == '>' || sep == '<')
				if (quote_check(split[i].word, err, i, nb_word) == -1)
					return (-1);
			err->sw = 1;
		}
		else
			err->sw = 0;
		i++;
	}
	return (0);
}
