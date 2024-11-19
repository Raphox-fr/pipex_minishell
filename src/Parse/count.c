//
// Created by umbra on 9/23/24.
//

# include "../../includes/Parsing.h"

int	state_in_view(const char *command, const int i)
{
	if (command[i] == '\"')
		return (D_QUOTE);
	if (command[i] == '\'')
		return (QUOTE);
	if (is_oper(command[i]))
		return (OPER);
	return (SPACES);
}

int	len_of_word(char *command, int i)
{
	t_token	token;

	token.len_word = 0;
	token.nb_word = 0;
	token.state = RESET;
	token.sep = ' ';
	return (r_value(command, i, &token));
}

int	nb_words(char *command)
{
	t_token token;

	token.len_word = -1;
	token.nb_word = 0;
	token.state = RESET;
	token.sep = ' ';
	return (r_value(command, 0, &token));
}

int	nb_command(t_split *split, int count_word)
{
	int count;
	int k;

	count = 1;
	k = 0;
	while (k < count_word)
	{
		if ((ft_strncmp(split[k].word, "|", 1) == 0) || (ft_strncmp(split[k].word, ";", split[k].len_word) == 0))
			count++;
		k++;
	}
	printf("nb_command : %d\n", count);
	return (count);
}