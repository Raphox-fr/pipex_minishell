//
// Created by umbra on 12/10/24.
//
# include "../../includes/minishell.h"

void	free_all(t_var *var, char **env, char *rule, int ext)
{
	if (rule)
		free(rule);
	if (var)
		free_var(var);
	if (env)
		free_env(env);
	rl_clear_history();
	if (ext != -1)
		exit (ext);
}