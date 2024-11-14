//
// Created by umbra on 11/7/24.
//
#include "../../includes/minishell.h"
#include "../../includes/Parsing.h"

static int find_var_in_quote(const char *buff, int len)
{
	int i;
	unsigned int	var_count;

	i = 0;
	var_count = 0;
	while (i < len)
	{
		if (buff[i] == '$')
			var_count++;
		i++;
	}
	return (var_count);
}

static int size_alloc_s_quote(const t_split *split, const char *command, t_variable *var, const int nb_var)
{
	int i;
	int k;
	int size_var;
	int size_name_var;

	i = 0;
	k = 0;
	size_var = 0;
	size_name_var = 0;
	if (find_var_in_quote(command, split->len_word))
	{
		while (command[i] && i < split->len_word)
		{
			while (command[i] != '$' && i < split->len_word)
				i++;
			if (command[i] == '$' && command[i] && i != split->len_word)
			{
				i++;
				while (k < nb_var) {
					if (ft_strncmp(command + i, var[k].name, ft_strlen(var[k].name)) == 0)
						break;
					k++;
				}
				if (k == nb_var)
					break;
				size_var += ft_strlen(var[k].value);
				size_name_var += ft_strlen(var[k].name);
			}
		}
	}
	return (((split->len_word - (size_name_var + 1)) + size_var - 2)); // +1 pour le $ et -2 pour les quote
}

static void is_double_quote(t_split *split, char *command)
{
	split->word = ft_calloc(sizeof(char), split->len_word);
	if (!split->word)
		return ;
	ft_strlcpy(split->word, command + 1, split->len_word - 1);
}

static void is_simple_quote(t_split *split, char *command, t_variable *var, int nb_var)
{
	split->word = ft_calloc(sizeof(char), split->len_word);
	if (!split->word)
		return ;
	ft_strlcpy(split->word, command + 1, split->len_word - 1);
}

void	add_quote(t_split *split, char *command, t_variable *var, int nb_var)
{
	if (!command)
		return ;
	if (command[0] == '\'')
		is_simple_quote(split, command, var, nb_var);
	else if (command[0] == '\"')
		is_double_quote(split, command);
}