/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:39:14 by thodos-s          #+#    #+#             */
/*   Updated: 2024/12/04 14:47:32 by thodos-s         ###   ########.fr       */
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
	while (temp_var != NULL && ft_strncmp(command , temp_var->name, ft_strlen(temp_var->name)) != 0)
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
		*var = elem;
	else
	{
		temp = (*var);
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = elem;
	}
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

static void	change_value(char *elem, t_var *var)
{
	int i;
	int	size;

	i = 0;
	size = 0;
	if (var == NULL)
		return ;
	free(var->value);
	while (elem[i] && elem[i] != '=')
		i++;
	if (elem[i] == '=')
		i++;
	else
		return ;
	while (elem[i + size] && !ft_isspace(elem[i + size]))
		size++;
	var->value = ft_calloc(sizeof(char), size + 1);
	ft_strlcpy(var->value, elem + i, size + 1);
}

static	t_var *give_var_adrr(char *command, t_var **var)
{
	t_var *temp;

	temp = *var;
	if ((temp) == NULL)
		return (NULL);
	while ((temp) != NULL && ft_strncmp(command, (temp)->name, ft_strlen((*var)->name)) != 0)
		(temp) = (temp)->next;
	if ((temp) == NULL)
		return (NULL);
	return (temp);
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
		change_value(command, give_var_adrr(command, var));
		return (0);
	}
	temp_var = ft_calloc(sizeof(t_var), 1);
	if (!temp_var)
		return (-1);
	temp_var->next = NULL;
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
	if (var_exist(command + 1, var) == 1)
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

char	*var_adder(char *buff, t_var **var)
{
	int	i;
	int	len;

	i = 0;
	while (buff[i] && ft_isspace(buff[i]))
		i++;
	while (buff[i] && find_var(buff + i) == 1)
	{
		printf("before rank : %d | car : %c\n", i, buff[i]);
		len = len_of_word(buff, i);
		add_var(var, buff + i, len);
		i += len;
		printf("rank : %d | car : %c\n", i, buff[i]);
		while (ft_isspace(buff[i]) || ft_strncmp(buff + i, "; ", 2) == 0)
			i++;
	}
	return (buff + i);
}