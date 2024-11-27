#ifndef MINISHELL_H
# define MINISHELL_H


# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# include <fcntl.h>
# include <string.h>
# include "stdbool.h"
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/errno.h>
# include <readline/history.h>
# include <readline/readline.h>

# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include <signal.h>

# include "libft.h"
# include "stdbool.h"
# include "Parsing.h"
# include "parsing_error.h"
# include "struct_shell.h"

# define PROMPT "Minishell-> "

// MAIN -------------------------------------------------------------------------------------

int count_data(t_data_rule *data);
char **ft_strdup_env(char **envp);


// PIPEX -----------------------------------------------------------------------------------------------

char **pipex(t_data_rule *data, int num_commands, char **envv);

void wait_for_children(void);
void free_command(char **cmd);
void execute(t_data_rule data, char **envp, int *p_fd);
void execution_process(t_data_rule data, char **env, int *input_fd, int *p_fd, int is_last_cmd);
void second_process(int *input_fd, int *p_fd, int is_last_cmd);
void do_pipe(t_data_rule data, char **env, int *input_fd, int is_last_cmd);
void exit_with_error(char *msg);


// BUILD COMMAND . C ---------------------------------------------------------------------------------------------

char *join_options(char **options);
char    **split_options(char *options, int *option_count);
char    **allocate_command(int option_count, int nbr_args);
int     copy_command(char **cmd, char *command);
int     copy_options(char **cmd, char **split_command, int i, int option_count);
int     copy_arguments(char **cmd, char **arguments, int i, int nbr_args);
char    **initialize_command(char *command, char **split_command, int option_count, int nbr_args);
char    **build_command(t_data_rule data);


// TOOLS . C ---------------------------------------------------------------------------------------------

void wait_for_children(void);
void handle_heredoc(char *delimiter);
void handle_redirection(t_data_rule data);
void handle_exit_redirections(char oper, char *output);
char	*find_path(char *cmd, char **envv);


// SPLIT . C ---------------------------------------------------------------------------------------------

char	**ft_my_split(char *s, char c);


// BUILTINS . C ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


char **exec_builtins(t_data_rule struc, char **envv);
int check_if_in_builtins(t_data_rule struc, char **envp);

//Echo
char **cd(char *command, char **arguments, char **envp);

//Echo
void echo(char *command, char **option, char **arguments);
void display_echo(char *command, char **option, char **arguments, char *result);

//Env
void display_env(char **envp); // env

//Export
char **export(char *command, char **arguments, char **envv);
char **cmd_export(char *command, char *arguments, char **env); // ajouter variable a l env 2 ou+ 
char	**allocate_new_env_to_add_variable(char **env, char *arguments);
int		size_env(char **env, char **new_env);


//Pwd
void pwd(char *command, char **envv); // recopie pwd

//Unset
char **unset(char *command, char **arguments, char **envp);
char **cmd_unset(char **env, char *var);  // retirer variable de l env
int check_var(char *str, int i, char **envv);


// ERROR . C
void	free_env(char **env);
void	handle_free(char **envp);
void error(int i, char *str);
void    free_command(char **cmd);

//TOOLS BUILT. C ------------------------------------------------------------------------------------------

void swap(char **a, char **b);
int	find_in_envv(char **envv, char *var);
void	bubble_sort(char **envp);
void display_x_variables(char **result);
int compare_strings(char *str1, char *str2);



char **ft_strdup_env(char **envp);
char **copy_the_env(char **envp);

#endif
