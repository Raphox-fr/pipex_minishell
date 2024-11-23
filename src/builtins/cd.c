/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:30:17 by raphox            #+#    #+#             */
/*   Updated: 2024/11/21 17:40:13 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **cd(char *command, char **arguments, char **envp)
{
	char *buffer;

	int index;
	index = 0;

	int pin;
	pin = 0;

	
	char *oldpwd;
	oldpwd = getenv("OLDPWD");

	char *pwd;
	pwd = getenv("PWD");
	

	if (command != 0 && arguments == NULL) // > cd (fait mais inutile, car pas demander)
	{
		//OLD PWD
		write(2, "CHJKDCHJCK", 10);
		pin = find_in_envv(envp, "PWD");
		index = find_in_envv(envp, "OLDPWD");
		buffer = ft_strjoin("OLDPWD=", envp[pin] + 4, 0);
		free(envp[index]);
		envp[index] = ft_strdup(buffer);
		free(buffer);
		
		//PWD
		pin = find_in_envv(envp, "PWD");
		index = find_in_envv(envp, "USER");
		buffer = ft_strjoin("PWD=/home/", envp[index] + 5, 0);
		free(envp[pin]);
		envp[pin] = ft_strdup(buffer);
		chdir(buffer);
		free(buffer);
		return (envp);
	}		
	
		// printf("%s",getenv("PWD"));
	else if (command != 0 && arguments != 0 && (arguments[0][0] == '/')) // > cd "arguments"
	{
		//OLD PWD
		pin = find_in_envv(envp, "PWD");
		index = find_in_envv(envp, "OLDPWD");
		buffer = ft_strjoin("OLDPWD=", envp[pin] + 4, 0);
		free(envp[index]);
		envp[index] = ft_strdup(buffer);
		free(buffer);
		//PWD
		index = find_in_envv(envp, "PWD");
		buffer = ft_strjoin("PWD=", arguments[0], 0);
		free(envp[index]);
		envp[index] = ft_strdup(buffer);
		chdir(buffer);
		free(buffer);
		return (envp);
	}

	else if ((command != 0 && arguments != 0 && arguments[0][0] != '/'))
	{
		char *pwd;
		char *short_path;
		char *result_path;
		

		char slash[] = "/";
		pwd = getenv("PWD");
		
		short_path = ft_strjoin(pwd, slash, 0);
		result_path = ft_strjoin(short_path, arguments[0], 0);


		//OLD PWD
		pin = find_in_envv(envp, "PWD");
		index = find_in_envv(envp, "OLDPWD");
		buffer = ft_strjoin("OLDPWD=", envp[pin] + 4, 0);
		free(envp[index]);
		envp[index] = ft_strdup(buffer);
		free(buffer);
		
		//PWD
		index = find_in_envv(envp, "PWD");
		buffer = ft_strjoin("PWD=", result_path, 0);
		free(envp[index]);
		envp[index] = ft_strdup(buffer);
		free(buffer);
		chdir(result_path);
		free(short_path);
		free(result_path);
		return (envp);
	}
	return (NULL);
}



// int main(int argc, char **argv, char **envp)
// {
// 	char command[] = "cd";
// 	char arguments[] = "/home/raphox/Desktop";
// 	// printf("%s", envp[3]);
// 	cd(command, arguments, envp);
// }