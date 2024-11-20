//
// Created by umbra on 10/1/24.
//

#ifndef MINISHELL_42_PARSING_ERROR_H
#define MINISHELL_42_PARSING_ERROR_H

# define ERR_SYX "bash: syntax error near"
# define ERROR_FD 2

typedef struct	s_erreur
{
	int	sw;
	int error_code;
	char c;
}				t_erreur;

void print_parsing_error(t_erreur err);

enum {STX_NL, SYNTAX, D_SYNTAX, STX_ALLOC};

#endif //MINISHELL_42_PARSING_ERROR_H
