//
// Created by umbra on 11/13/24.
//

#ifndef MINISHELL_42_STRUCT_SHELL_H
#define MINISHELL_42_STRUCT_SHELL_H

# include "stdbool.h"

typedef struct	s_var
{
	char 			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct	s_data_rule
{
	char	*command;
	char 	**options;
	char 	**arguments;
	int 	nbr_args;
	char	*dir_path;
	char	**out;
	char	*input;
	int		nb_rdir;
	int 	nb_opt;
	char 	*oper;
	bool 	pipe;
	int 	nb_command;
	t_var	*var;
}				t_data_rule;

#endif //MINISHELL_42_STRUCT_SHELL_H


	// if (data.oper != NULL)// Execution redirections
	// {
	// 	if if (data.oper[0] == 'h')
	// 	{
	// 		if (handle_redirection(data) == -1)
	// 	{
	// 			free_env(cmd);
	// 			free_env(envp);
	// 			envp = NULL;
	// 			exit(EXIT_FAILURE);
	// 		}	
	// 	}
	// }

			// 	if (data.oper != NULL && data.oper[0] == 'h')
			// {
			// 	handle_redirection(data);
			// }