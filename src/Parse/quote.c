/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:33:22 by thodos-s          #+#    #+#             */
/*   Updated: 2024/12/04 11:33:31 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/Parsing.h"

t_var	*give_var(char *command, t_var **var)
{
	t_var *temp_var;

	temp_var = NULL;
	if (!command || !(*var))
		return (NULL);
	temp_var = *var;
	while (temp_var != NULL && ft_strncmp(command, temp_var->name, ft_strlen(temp_var->name)) != 0)
		temp_var = temp_var->next;
	if (temp_var != NULL)
		return (temp_var);
	return (NULL);
}

static int	find_size(char *buff, const int len, t_var **var)
{
	int i;
	int size;
	t_var *temp;

	size = 0;
	i = 0;
	while (i < len)
	{
		if (buff[i] == '$' && var_exist(buff + i + 1, var))
		{
			temp = give_var(buff + i + 1, var);
			if (temp != NULL)
			{
				size += ft_strlen(temp->value);
				i += ft_strlen(temp->name) + 1;
			}
		}
		size++;
		i++;
	}
	printf("size : %d\n", size);
	return (0);
}

static void	is_simple_quote(t_split *split, char *command)
{
	split->word = ft_calloc(sizeof(char), split->len_word);
	if (!split->word)
		return ;
	ft_strlcpy(split->word, command, split->len_word);
}

static void	is_double_quote(t_split *split, char *command, t_var **var)
{
	int itr_word;
	int	itr_cmd;
	t_var *temp_var;

	itr_word = 0;
	itr_cmd = 0;
	temp_var = NULL;
	if (command == NULL)
		return ;
	split->word = ft_calloc(sizeof(char), find_size(command, split->len_word, var) + 1);
	if (!split->word)
		return ;
	printf("len_word : %d\n", split->len_word);
	while (itr_cmd < split->len_word - 1)
	{
		if (command[itr_cmd] == '$' && var_exist(command + itr_cmd + 1, var))
		{
			temp_var = give_var(command + itr_cmd + 1, var);
			ft_strlcpy(split->word + itr_word, temp_var->value, ft_strlen(temp_var->value) + 1);
			itr_cmd += ft_strlen(temp_var->name) + 1;
			printf("size name : %d\n", ft_strlen(temp_var->name));
			itr_word += ft_strlen(temp_var->value);
			printf("size value : %d\n", ft_strlen(temp_var->value));
		}
		else
		{
			split->word[itr_word] = command[itr_cmd];
			itr_word++;
			itr_cmd++;
		}
	}
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
		is_simple_quote(split, command);
	else if (command[0] == '\"')
		is_double_quote(split, command, var);
	(*index)++;
}