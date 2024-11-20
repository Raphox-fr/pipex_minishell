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

t_variable	*give_var(t_variable *var, const char *command,
			const int len_word, const int nb_var)
{
	int	k;

	k = 0;
	while (k < nb_var)
	{
		if (ft_strncmp(var[k].name, command, len_word))
			break ;
		k++;
	}
	if (k == nb_var)
		return (NULL);
	return (&var[k]);
}

int	find_var(char *command)
{
	int		i;
	int		count_var;

	i = 0;
	count_var = 0;
	while (command[i])
	{
		if (command[i] == '=')
			count_var++;
		i++;
	}
	return (count_var);
}

int	add_var(t_variable *var, char *command, int len)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < len && command[i] != '=')
		i++;
	if (!command[i])
		return (0);
	var->name = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(var->name, command, i + 1);
	i++;
	k = i;
	while (i <= len && command[i] != ' ')
		i++;
	var->value = ft_calloc(sizeof(char), i - k + 1);
	ft_strlcpy(var->value, command + k, (i - k) + 1);
	return (1);
}

int	test_var(char *dest, const char *command, t_variable *var, const int nb_var)
{
	int	i;

	i = 0;
	if (command[0] != '$')
		return (0);
	command++;
	while (i < nb_var)
	{
		if (ft_strncmp(command, var[i].name, ft_strlen(var[i].name)) == 0)
			break ;
		i++;
	}
	if (i == nb_var)
		return (0);
	if (ft_strncmp(command, var[i].name, ft_strlen(var[i].name)) != 0)
		return (-1);
	ft_strlcpy(dest, var[i].value, ft_strlen(var[i].value));
	return (1);
}

int	fill_var(t_split *split, char *command, t_variable **var, int nb_var)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < split->len_word && command[i] != '$')
		i++;
	if (command[i] == '$')
		i++;
	while (k < nb_var)
	{
		if (ft_strncmp(command + i, var[k]->name, ft_strlen(var[k]->name)) == 0)
			break ;
		k++;
	}
	if (k == nb_var)
		return (0);
	if (ft_strncmp(command + i, var[k]->name, ft_strlen(var[k]->name)) != 0)
		return (-1);
	split->word = ft_calloc(sizeof(char), ft_strlen(var[k]->value));
	if (!split->word)
		return (-1);
	ft_strlcpy(split->word, var[k]->value, ft_strlen(var[k]->value));
	return (0);
}
