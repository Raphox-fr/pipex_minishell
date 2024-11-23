/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:47:30 by raphox            #+#    #+#             */
/*   Updated: 2024/11/21 17:40:36 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// envp deja copier auparavant !!!!!! sinon ne marche pas !!!!!!!

#include "minishell.h"

char **unset(char *command, char **arguments, char **envp)
{
	int i;
	i = 0;

	if (arguments == NULL)
	{
		return (envp);
	}
	
	else
		while (arguments[i])
		{
			envp = cmd_unset(envp, arguments[i++]);
		}
		
	return (envp);
		
}

char	**cmd_unset(char **env, char *var)
{
	int i;
	i = 0;

	if (var == NULL)
		return (env);
	
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0 && check_var(var, i, env) == 1)
		{
			free(env[i]);
			while (env[i] != NULL) // ca decale les autres variables
			{
				env[i] = env[i + 1];
				i++;
			}
			// free(env[i]); // supp la variable en faisant free
			return (env);
		}
		i++;
	}
	return (env);
}


int check_var(char *str, int i, char **envv)
{
	int size;
	size = 0;
	
	int size_var;
	size_var = ft_strlen(str);

	while (str[size])
	{
		if (str[size] == '=')
			return (0);
		size++;
	}
	return (1);
	
}

// int main(int argc, char **argv, char **envp)
// {
// 	char **enviro;
// 	enviro = copy_env(envp);
// 	enviro = unset_var(enviro, argv[1]);
// 	return (0);

// }