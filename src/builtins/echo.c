/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:10:56 by raphox            #+#    #+#             */
/*   Updated: 2024/11/26 13:13:52 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void echo(char *command, char **option, char **arguments)
{
    int i;
    char *result;
    char *temp;

    i = 0;
	
    result = ft_strdup("");
    if (arguments != NULL)
    {
        free(result);
        result = ft_strdup(arguments[0]);
        i = 1;
        while (arguments[i] != NULL)
        {
            temp = ft_strjoin(result, arguments[i], 1);
            free(result);
            result = temp;
            i++;
        }
    }
	display_echo(command, option, arguments, result);
    free(result);
}


void display_echo(char *command, char **option, char **arguments, char *result)
{
	
	if (command != NULL && option == 0 && arguments == 0)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (command != NULL && option != NULL && option[0][0] == '-' && option[0][1] == 'n' && option[0][2] == '\0' && arguments == 0)
		return ;
	
	else if (command != NULL && option == NULL && arguments != NULL)
	{
		write(1, result, ft_strlen(result)); // back slash a mettre 
		write(1, "\n", 1); // back slash a mettre
	}
	else if (command != NULL && option != NULL && option[0][0] == '-' && option[0][1] == 'n' && option[0][2] == '\0' && arguments != 0)
	{
		write(1, result, ft_strlen(result)); // pas de saut de ligne avec -n
	}
	return ;
}
