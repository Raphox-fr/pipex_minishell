//
// Created by umbra on 10/3/24.
//
#include "../../includes/Parsing.h"
#include "../../includes/minishell.h"

static int 	node_finish(char *buff, int len)
{
	if (!buff || buff == NULL)
		return (1);
	if (ft_strncmp(buff, "|", len) == 0 || check_rdir(buff, len) != OTHER)
		return (1);
	return (0);
}

int	check_rdir(char *buff, int len)
{
	if (ft_strncmp(buff, ">", len) == 0)
		return (RDIR);
	if (ft_strncmp(buff, "<", len) == 0)
		return (INPUT);
	if (ft_strncmp(buff, ">>", len) == 0) // remplacer par une boucle comme ca si c4est plus de 2 error
		return (D_RDIR);
	if (ft_strncmp(buff, "|", len) == 0)
		return (PIPE);
	else
		return (OTHER);
}

int check_first(const t_split *split, int i)
{
	int k;
	int quote;

	k = 0;
	quote = 0;
	while (split[i].word[k])
	{
		if (split[i].word[k] == '\"')
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		if (split[i].word[k] == '=' && quote)
			return (VARIABLE);
	}
	return (OTHER);
}

int r_node(t_split *split, int nb_node)
{
	int node_type;

	node_type = 0;
	if (split[nb_node].word == NULL)
		return (nb_node);
	if (node_finish(split[nb_node].word, split[nb_node].len_word))
		return (nb_node);
	node_type = check_rdir(split->word, split->len_word);
	if (node_type == OTHER)
	{
		nb_node++;
		return (r_node(split, nb_node));
	}
	else if (node_type == RDIR)
		return (r_node(split, nb_node));
}

int ft_nbr_option(const t_split *split, const int nb_node)
{
	int nb_opt;
	int i;

	i = 0;
	nb_opt = 0;
	if (!split)
		return (0);
	while (i < nb_node - 1)
	{
		if (split[i].word[0] == '-')
			nb_opt++;
		if (split[i].word[0] != '-')
			break ;
		i++;
	}
	return (nb_opt);
}