//
// Created by umbra on 11/12/24

#include "../../includes/minishell.h"
#include "../../includes/Parsing.h"

int add_semicolon(t_split *split)
{
	if (split->word && ft_strncmp(split->word, ";", split->len_word) == 0)
		return (1);
	return (0);
}

static int	add_out_request(t_data_rule *request, t_split *split, int itr_oper)
{
	printf("in add out split : %s\n", split[0].word);
	if (split->word != NULL)
	{
		request->out[itr_oper] = split->word;
		return (2);
	}
	return (0);
}

static int	add_input_request(t_data_rule *request, t_split *split)
{
	if (!split)
		return (0);
	request->input = split->word;
	return (1);
}

int add_arg_request(t_data_rule *request, t_split  *split, int nb_node)
{
	int itr_arg;

	itr_arg = 0;
	if (!split)
		return (-1);
	request->arguments = ft_calloc(sizeof(char *), nb_node + 1);
	while (itr_arg < nb_node - 1)
	{
		request->arguments[itr_arg] = split[itr_arg].word;
		itr_arg++;
	}
	return (itr_arg);
}

int add_rdir(t_data_rule *request, t_split *split, const int count_word)
{
	int count_output;
	int itr_oper;
	int itr;

	count_output = 0;
	itr_oper = 0;
	itr = 0;
	if (!split)
		return (0);
	request->out = ft_calloc(sizeof(char *), request->nb_rdir + 1);
	if (!request->out)
		return (0);
	while (split[itr].word != NULL && ft_strncmp(split[count_output].word, "|", split[count_output].len_word) != 0)
	{
		if ((request->oper[itr_oper]) == '<' || request->oper[itr_oper] == 'h')
		{
			itr++;
			add_input_request(request, split + itr);
			add_out_request(request, split + itr, itr_oper);
			itr_oper++;
		}
		else if ((request->oper[itr_oper] == '>' || request->oper[itr_oper] == 'r'))
		{
			itr++;
			add_out_request(request, split + itr, itr_oper);
			itr_oper++;
		}
		itr++;
	}
	return (itr);
}