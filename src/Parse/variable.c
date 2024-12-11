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

typedef struct temp temp;

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

static void	add_val(t_var *temp, char *cmd, int *i)
{
	int k;
	bool	quote;

	k = *i;
	quote = false;
	while (cmd[*i])
	{
		if (cmd[*i] == '\"' && quote == false)
				quote = true;
		else if (cmd[*i] == '\"' && quote == true)
				quote = false;
		if (cmd[*i] == ' ' && quote == false)
			break ;
		*i += 1;
	}
	temp->value = ft_calloc(sizeof(char), *i - k + 1);
	if (!temp->value)
		return ;
	if (cmd[*i] == '\"')
		ft_strlcpy(temp->value, cmd + k, (*i - k) + 1);
	else
		ft_strlcpy(temp->value, cmd + k + 1, (*i - k) - 1);
}

static void	add_name(t_var *temp, char *cmd, int *i)
{
	while (cmd[*i] && cmd[*i] != '=')
		*i += 1;
	if (!cmd[*i])
		return ;
	temp->name = ft_calloc(sizeof(char), *i + 1);
	if (!temp->name)
		return ;
	ft_strlcpy(temp->name, cmd, *i + 1);
	*i += 1;
}

int	add_var(t_var **var, char *command, int len)
{
	int	i;
	t_var *temp_var;

	i = 0;
	(void)len;
	if (var_exist(command, var))
	{
		change_value(command, give_var_adrr(command, var));
		return (0);
	}
	temp_var = ft_calloc(sizeof(t_var), 1);
	if (!temp_var)
		return (-1);
	temp_var->next = NULL;
	add_name(temp_var, command, &i);
	if (temp_var->name == NULL)
		return (-1);
	add_val(temp_var, command, &i);
	add_back(var, temp_var);
	while (ft_isspace(command[i]))
		i++;
	if (ft_strncmp(command + i, ";", 1) == 0)
		command[i] = ' ';
	return (i);
}

/*static int	fill_var(char **out, int *len_word, char *command, t_var **var)
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
		*out = ft_calloc(sizeof(char), ft_strlen(temp->value) + 1);
		ft_strlcpy(*out, temp->value, ft_strlen(temp->value) + 1);
	}
	else
		return (0);
	*len_word = ft_strlen((*var)->value);
	return (1);
}*/

static char	*fill_var(char *buff, int i, t_var **var)
{
	char	*out;
	t_var *temp;

	temp = NULL;
	out = NULL;
	if (buff[i] != '$')
		return (0);
	if (var_exist(buff + i + 1, var) == 1)
	{
		temp = give_var(buff + i + 1, var);
		if (temp == NULL)
			return (ft_memset(buff + i, ' ', ft_strcspn(buff, " ")));
		out = ft_calloc(sizeof(char), i);
		ft_strlcpy(out, buff, i + 1);
		out = ft_strjoin(out, temp->value, 0);
		i += ft_strlen(temp->name) + 1;
		if (i < ft_strlen(buff))
			out = ft_strjoin(out, buff + i, 0);
		free(buff);
	}
	return (out);
}

char	*var_adder(char *buff, t_var **var)
{
	int		i;
	int		len;
	char	*cmd;

	i = 0;
	cmd = NULL;
	while (buff[i] && ft_isspace(buff[i]))
		i++;
	while (buff[i] && find_var(buff + i) == 1)
	{
		len = add_var(var, buff + i, len);
		i += len;
		while (ft_isspace(buff[i]) || ft_strncmp(buff + i, "; ", 2) == 0)
			i++;
	}
	while (buff[i])
	{
		if (buff[i] == '$')
			buff = fill_var(buff, i, var);
		printf("after : %s\n", buff);
		i++;
	}
	return (buff + i);
}