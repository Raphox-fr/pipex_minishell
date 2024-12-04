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

int var_exist(char *command, t_var **var)
{
	t_var *temp_var;

	temp_var = NULL;
	if ((*var) == NULL)
		return (0);
	temp_var = *var;
	if (command[0] != '$')
		return (0);
	while (temp_var != NULL && ft_strncmp(command + 1, temp_var->name, ft_strlen(temp_var->name)) != 0)
		temp_var = temp_var->next;
	if (temp_var != NULL)
		return (1);
	return (0);
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
	temp->next = elem;
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

void print_var(t_var *var)
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

static void	change_value(char *elem, t_var **var)
{
	int i;

	i = 0;
	if ((*var) == NULL)
		return ;
	free((*var)->value);
	while (elem[i] && elem[i] != ft_isspace(elem[i]))
		i++;
	(*var)->value = ft_calloc(sizeof (char), i + 1);
	ft_strlcpy((*var)->value, elem, i + 1);
}

static	t_var **give_var_adrr(char *command, t_var **var)
{
	if ((*var) == NULL)
		return (NULL);
	while ((*var) != NULL && ft_strncmp(command, (*var)->name, ft_strlen((*var)->name)) != 0)
		(*var) = (*var)->next;
	if ((*var) == NULL)
		return (NULL);
	return (&(*var));
}

int	add_var(t_var **var, char *command, int len)
{
	int	i;
	int	k;
	t_var *temp_var;

	i = 0;
	k = 0;
	if (var_exist(command, var))
	{
		printf("exist deja");
		change_value(command, give_var_adrr(command, var));
		return (0);
	}
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
	while (ft_isspace(command[i]))
		i++;
	if (ft_strncmp(command + i, ";", 1) == 0)
		command[i] = ' ';
	return (1);
}

int	fill_var(char **out, int *len_word, char *command, t_var **var)
{
	int	i;
	t_var *temp;

	temp = NULL;
	i = 0;
	if (command[i] != '$')
		return (0);
	if ((*var) == NULL)
		return (0);
	if (var_exist(command, var) == 1)
	{
		temp = give_var(command + 1, var);
		if (temp == NULL)
			return (0);
		printf("temp : %s\n", temp->value);
		*out = ft_calloc(sizeof(char), ft_strlen(temp->value) + 1);
		ft_strlcpy(*out, temp->value, ft_strlen(temp->value) + 1);
		printf("out : %s\n", *out);
	}
	else
		return (0);
	printf("out : %s\n", *out);
	*len_word = ft_strlen((*var)->value);
	return (1);
}