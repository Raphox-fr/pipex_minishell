#ifndef MINISHELL_H
# define MINISHELL_H


# include <stdio.h>
# include <stdlib.h>
# include<stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include "libft.h"
# include "stdbool.h"
# include "Parsing.h"
# include "parsing_error.h"

# define PROMPT "Minishell-> "
#ifndef DEBUG
# define DEBUG 0
#endif

// extern int genvu;

typedef struct 	s_data_rule
{
	// char	**envv;
	char	*command;
	char **options;
	char 		**arguments;
	int 	nbr_args;
	char	*dir_path;
	char	*out; // il faut free
	char	*input;
	char 	oper; // r = >>
	bool 	pipe;
	int 	nb_command;
}				t_data_rule;

// Main.c
t_data_rule		*parsing(char *command, t_erreur *err); // verification du token et decoupage dans la structure
char			*lexing(char *brut_rules); // transformation de commande en token
// BUILTINS.C ------------------------------------------------------------------------------

void exec_builtins(t_data_rule struc, char **genv);
//Echo
void cd(char *command, const char **arguments, char **envp);

//Echo
void echo(char *command, char *option, const char **arguments);
void display_echo(char *command, char *option, const char **arguments, char *result);

//Env
void display_env(char **envp); // env

//Export
char **export(char *command, const char **arguments, char **env);
char **cmd_export(char *command, const char *arguments, char **env); // ajouter variable a l env 2 ou+ 
char	**allocate_new_env(char **env);
int		copy_env(char **env, char **new_env);

//Pwd
void pwd(char *command, char **envv); // recopie pwd

//Unset
char **unset(char *command, const char **arguments, char **envp);
char **cmd_unset(char **env, const char *var);  // retirer variable de l env

//TOOLS.C ------------------------------------------------------------------------------------------

void swap(char **a, char **b);
int	find_in_envv(char **envv, char *var);
void	bubble_sort(char **envp);
void display_x_variables(char **result);
int compare_strings(const char *str1, const char *str2);


// PIPEX ------------------------------------------------------------------------------------------

int pipex(int ac, char **av, char **envp);
void do_pipe(char *cmd, char **env, int *input_fd, int is_last_cmd);
void handle_parent_process(int *input_fd, int *p_fd, int is_last_cmd);
void wait_for_children(void);
void handle_child_process(char *cmd, char **env, int *input_fd, int *p_fd, int is_last_cmd);
void close_pipes(int *pipes);

//ERROR.C ------------------------------------------------------------------------------------------
void free_env(char **env);

#endif
