/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:35:49 by raphox            #+#    #+#             */
/*   Updated: 2024/12/02 15:55:57 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd(char *command, char **envv)
{
	int index;
	index = find_in_envv(envv, "PWD");
	
	 if (ft_strncmp(command, "pwd", ft_strlen(command)) == 0)
	{
		write(1, envv[index] + 4, ft_strlen(envv[index] + 4));
		write(1, "\n", 1);
	}
	return ;

}

// int main(int agrc, char **argv, char **envp)
// {
// 	pwd("pwd", "", envp);
	
// }