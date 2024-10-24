//
// Created by umbra on 9/16/24.
//

#ifndef MINISHELL_42_LEXING_H
#define MINISHELL_42_LEXING_H

# include "minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "parsing_error.h"

typedef struct	s_token
{
	char	sep;
	int 	state;
	int		nb_word;
	int 	len_word;
}				t_token;

typedef struct	s_variable
{
	char	*name;
	char	*value;
}				t_variable;

typedef struct	s_split
{
	char 	sep;
	int		len_word;
	char 	*word;
	int 	state;
}				t_split;

char	*delete_space(char *command);
int	nb_words(char *command);
int	r_value(char *command, int i, t_token *token);
int	is_oper(char c);
int	ft_isspace(char c);
int	state_finish(t_token *token);
int	ft_isend(const char c);
int	state_in_view(const char *command, const int i);
int	len_of_word(char *command, int i);
int	nb_command(t_split *split, int count_word);
int request_count(t_split *split, int count_word);
struct s_data_rule	*parsing_tree(t_split *split, const int count_word);
int r_node(t_split *split, int i);
int	check_rdir(char *buff, int len);
int	syntax_check(t_split *split, const int nb_word, struct s_erreur *err);
int find_var(char *command);
int add_var(t_variable *var, char *command, int len);
int fill_var(t_split *split, char *command, t_variable *var);
void	killer_request(struct s_data_rule **request);

enum {RESET, SPACES, OPER, QUOTE, D_QUOTE};
enum {VARIABLE, INPUT, RDIR, D_RDIR, N_OPER, PIPE, OTHER};

#endif //MINISHELL_42_LEXING_H
