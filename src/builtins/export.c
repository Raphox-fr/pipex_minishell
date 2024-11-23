/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:28:32 by raphox            #+#    #+#             */
/*   Updated: 2024/11/21 17:40:29 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// envp est une copie ! ! ! ! !!


char	**export(char *command, char **arguments, char **envv)
{
	int		i;
	char	**result;
	char	**new_result;

	i = 0;
	result = envv;
	if (command != NULL && arguments == NULL)
	{
		bubble_sort(result);
		display_x_variables(result);
	}
	else
	{
		while (arguments[i] != NULL)
		{
			new_result = cmd_export(command, arguments[i++], result);
			result = new_result;
		}
	}
	return (result);
}



	
// Fonction cmd_export qui ajoute un nouvel argument à l'environnement
char	**cmd_export(char *command, char *argument, char **env)
{
	
	int check;
	char **new_env;

	check = 0;
	while (env[check] != NULL)
	{
		if ((ft_strncmp(env[check], argument, ft_strlen(env[check])) == 0))
			return (env);
		check++;
	}
	if (check_var(argument, 0, env) == 1)
		return (env);

	new_env = allocate_new_env_to_add_variable(env, argument);
	free_env(env);

	return (new_env);

	
}

// allouer nouvel environnement
char	**allocate_new_env_to_add_variable(char **env, char *arguments)
{
	int i;
	int		size;
	char	**new_env;

	i = 0;
	size = 0;
	
	while (env[size] != NULL)
		size++;
		
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arguments);
	new_env[++i] = NULL;
	return (new_env);
}







//-------------------------------------------------------------------------
