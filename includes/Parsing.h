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

typedef struct	s_split
{
	char 	sep;
	int		len_word;
	char 	*word;
	int 	state;
}				t_split;

int 		add_arg_request(t_data_rule *request, t_split  *split, const int nb_opt, const int nb_node);
int			add_command(t_data_rule *request, t_split *split);
int 		add_rdir(t_data_rule *request, t_split *split);
int 		add_var(t_var **var, char *command, int len);
int			add_pipe(t_data_rule *request, t_split *split, const int count_word);
void		add_quote(t_split *split, char *command, int *index, t_var ** var);
int			add_opt_request(t_data_rule *request, t_split *split, const int nb_opt);
int			add_semicolon(t_split *split);
int			braquet_check(char *str, t_erreur *err);
int			check_rdir(char *buff, int len);
char		*delete_space(char *command);
char 		*delete_inutile_quote(char *command);
int			evidence(char *command, t_erreur *err);
int			empty_braquet(char *str);
int			ft_nbr_option(const t_split *split, const int nb_node);
int			ft_nb_rdir(t_split *split);
int			ft_isspace(char c);
int			ft_isend(const char c);
void		fill_conv_rdir(t_data_rule *request, const int rdir, const int itr_oper);
int			fill_var(char **out, int *len_word, char *command, t_var **var);
void		fill_rdir(t_data_rule *request, t_split *split, int itr, int itr_oper);
int			find_var(char *command);
t_var	*give_var(char *command, t_var **var);
int			is_oper(char c);
int			nb_words(char *command);
int			state_finish(t_token *token);
int			state_in_view(const char *command, const int i);
int			len_of_word(char *command, int i);
int			nb_command(t_split *split, int count_word);
int 		node_finish(char *buff, int len);
int 		request_count(t_split *split, int count_word);
struct s_data_rule		*parsing(char *command, t_var **var, t_erreur *err); // verification du token et decoupage dans la structure
struct s_data_rule	*parsing_tree(t_split *split, const int count_word);
int 		r_node(t_split *split, int i);
int			r_value(char *command, int i, t_token *token);
char		*var_adder(char *buff, t_var **var);
int var_exist(char *command, t_var **var);
int			syntax_check(t_split *split, const int nb_word, struct s_erreur *err);
void		killer_request(struct s_data_rule *request);
void killer_split(t_split *split, const int nb_word);

void print_var(t_var *var);

enum {RESET, SPACES, OPER, QUOTE, D_QUOTE};
enum {OTHER, VARIABLE, INPUT, D_INPUT, RDIR, D_RDIR, N_OPER, PIPE};

#endif //MINISHELL_42_LEXING_H
