/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 16:29:11 by raphox            #+#    #+#             */
/*   Updated: 2024/11/25 18:06:48 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **exec_builtins(t_data_rule struc, char **envv)
{
	if (ft_strncmp(struc.command, "cd", ft_strlen(struc.command)) == 0) // modidfy env
	{
		envv = cd(struc.command, struc.arguments, envv);
		return (envv);
	}
	else if (ft_strncmp(struc.command, "echo", ft_strlen(struc.command)) == 0)
	{
		echo(struc.command, struc.options, struc.arguments);
		// valgrind valid
		return (envv);
	}
	else if (ft_strncmp(struc.command, "env", ft_strlen(struc.command)) == 0)
	{
		display_env(envv);
		// display_x_variables(envv);
		write(2, "env bien execute", 16);
		// valgrind valid
		return (envv);
	}
	else if (ft_strncmp(struc.command, "export", ft_strlen(struc.command)) == 0) // modidfy env
	{	
		write(2, "export bine executer", 20);
		envv = export(struc.command, struc.arguments, envv);
		// display_env(envv);
		return (envv);
	}
	else if (ft_strncmp(struc.command, "pwd", ft_strlen(struc.command)) == 0)
	{
		pwd(struc.command, envv);
		return (envv);
	}
	else if (ft_strncmp(struc.command, "unset", ft_strlen(struc.command)) == 0) // modidfy env
	{
			envv = unset(struc.command, struc.arguments, envv);
			return (envv);
	}
	return (envv);
}



int check_if_in_builtins(t_data_rule struc, char **envp)
{
	
	if (ft_strncmp(struc.command, "cd", ft_strlen(struc.command)) == 0) // modidfy env
		return(-1);
	else if (ft_strncmp(struc.command, "echo", ft_strlen(struc.command)) == 0)
		return(1);
	else if (ft_strncmp(struc.command, "env", ft_strlen(struc.command)) == 0)
		return(1);
	else if (ft_strncmp(struc.command, "export", ft_strlen(struc.command)) == 0) // modidfy env
		return(-1);
	else if (ft_strncmp(struc.command, "pwd", ft_strlen(struc.command)) == 0)
		return(1);
	else if (ft_strncmp(struc.command, "unset", ft_strlen(struc.command)) == 0) // modidfy env
		return(-1);
	return (0);
}
