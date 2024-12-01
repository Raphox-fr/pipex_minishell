/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:39:14 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 15:42:36 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

int	var_count(char *command)
{
	int nb_var;
	int itr;
	bool	quote;

	nb_var = 0;
	itr = 0;
	quote = false;
	while (command[itr])
	{
		while (command[itr] && (ft_isalpha(command[itr]) || command[itr] == '='))
		{
				if (command[itr] == '=' && quote == false)
					nb_var++;
				itr++;
		}
		if (command[itr] == '\"')
		{
			if (quote == false)
				quote = true;
			else
				quote = false;
		}
		itr++;
	}
	printf("%d\n", nb_var);
	return (nb_var);
}

void	add_back(t_var **var, t_var *elem)
{
	t_var	*temp;

	temp = NULL;
	if ((*var) == NULL)
	{
		*var = elem;
		return ;
	}
	temp = (*var);
	while (temp->next != NULL)
		temp = temp->next;
	temp = elem;
}

int	find_var(char *command)
{
	int		i;
	bool	dq;

	i = 0;
	dq = false;
	while (command[i])
	{
		if (command[i] == '\"' && dq == false)
			dq = true;
		else if (command[i] == '\"' && dq == true)
			dq = false;
		if (!ft_isalpha(command[i]) && command[i] != '=')
			return (0);
		if (command[i] == '=' && dq == false)
			return (1);
		i++;
	}
	return (0);
}

static void print_var(t_var *var)
{
	t_var	*temp;

	temp = var;
	printf("---------------\n");
	printf("var : \n");
	while (temp != NULL)
	{
		printf("name : %s\n", temp->name);
		printf("value : %s\n", temp->value);
		temp = temp->next;
	}
	printf("---------------\n");
}

int	add_var(t_var **var, char *command, int len)
{
	int	i;
	int	k;
	t_var *temp_var;

	i = 0;
	k = 0;
	temp_var = ft_calloc(sizeof(t_var), 1);
	if (!temp_var)
		return (-1);
	while (i < len && command[i] != '=')
		i++;
	if (!command[i])
		return (0);
	temp_var->name = ft_calloc(sizeof(char), i + 1);
	if (!temp_var->name)
		return (-1);
	ft_strlcpy(temp_var->name, command, i + 1);
	i++;
	k = i;
	while (i <= len && command[i] != ' ')
		i++;
	temp_var->value = ft_calloc(sizeof(char), i - k + 1);
	if (!temp_var->value)
		return (-1);
	ft_strlcpy(temp_var->value, command + k, (i - k) + 1);
	add_back(var, temp_var);
	return (1);
}

int	fill_var(t_split *split, char *command, t_var **var)
{
	int	i;

	i = 0;
	while (i < split->len_word && command[i] != '$')
		i++;
	if (command[i] == '$')
		i++;
	if ((*var) == NULL)
		return (0);
	while ((*var) != NULL)
	{
		if (ft_strncmp(command + i, (*var)->name, split->len_word) == 0)
			break ;
		(*var) = (*var)->next;
	}
	if (*var == NULL)
		return (0);
	split->word = ft_calloc(sizeof(char), ft_strlen((*var)->value) + 1);
	if (!split->word)
		return (-1);
	ft_strlcpy(split->word, (*var)->value, ft_strlen((*var)->value) + 1);
	split->len_word = ft_strlen((*var)->value);
	return (1);
}