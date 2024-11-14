#ifndef MINISHELL_42_LEXING_H
# define MINISHELL_42_LEXING_H

# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include "struct_shell.h"
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

int 	add_arg_request(t_data_rule *request, t_split  *split, int nb_node);
int 	add_rdir(t_data_rule *request, t_split *split, const int count_word);
int 	add_var(t_variable *var, char *command, int len);
void	add_quote(t_split *split, char *command, t_variable *var, int nb_var);
int braquet_check(char *str, t_erreur *err);
int	check_rdir(char *buff, int len);
char	*delete_space(char *command);
int evidence(char *command, t_erreur *err);
int ft_nbr_option(const t_split *split, const int nb_node);
int	ft_isspace(char c);
int	ft_isend(const char c);
int fill_var(t_split *split, char *command, t_variable **var, int nb_var);
int find_var(char *command);
t_variable *give_var(t_variable *var, const char *command, const int len_word, const int nb_var);
int	is_oper(char c);
int	nb_words(char *command);
int	state_finish(t_token *token);
int	state_in_view(const char *command, const int i);
int	len_of_word(char *command, int i);
int	nb_command(t_split *split, int count_word);
int request_count(t_split *split, int count_word);
struct s_data_rule		*parsing(char *command, t_erreur *err); // verification du token et decoupage dans la structure
struct s_data_rule	*parsing_tree(t_split *split, const int count_word);
int r_node(t_split *split, int i);
int	r_value(char *command, int i, t_token *token);
int	syntax_check(t_split *split, const int nb_word, struct s_erreur *err);
int occurence(char *str);
void	killer_request(struct s_data_rule *request);

int test_var(char *dest, const char *command, t_variable *var, const int nb_var);

enum {RESET, SPACES, OPER, QUOTE, D_QUOTE};
enum {OTHER, VARIABLE, INPUT, RDIR, D_RDIR, N_OPER, PIPE};

#endif //MINISHELL_42_LEXING_H
