/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_command_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:14:05 by raphox            #+#    #+#             */
/*   Updated: 2024/12/11 19:18:07 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int count_options(char **options, int *option_count)
{
    int i;
    i = 0;

    if (options == NULL)
    {
        *option_count = 0;
        return (0);
    }

    while (options[i] != NULL)
        i++;
    *option_count = i;
    return (1);
}

char *build_command(char *command)
{
	int i;
	int found;
	i = 0;

	found = 0;

	if (command == NULL)
		return (NULL);

	while (command[i] != '\0') // chemin en commande
	{
		if (command[i] == '/')
		{
			found = i + 1;
		}
		i++;
	}	
	if (found != 0)
	{
		if (access(command, F_OK | X_OK) == -1)
		{
			return (NULL);
		}
		return (ft_strdup(command + found));
	}
	else 
		return (ft_strdup(command));
}

void free_command_array(char **cmd)
{
    int i = 0;

    if (cmd == NULL)
        return;
    while (cmd[i] != NULL)
    {
        free(cmd[i]);
        i++;
    }
    free(cmd);
}

char **build_execution(t_data_rule data)
{
    int index;
    int i;
    char **cmd;
    int options_count;

    count_options(data.options, &options_count);

    cmd = malloc(sizeof(char *) * (1 + options_count + data.nbr_args + 1));
    if (cmd == NULL)
    {
        write(2, "Error: Memory allocation failed\n", 33);
        return (NULL);
    }

    index = 0;
    cmd[index] = build_command(data.command);
    if (cmd[index] == NULL)
    {
        // write(2, "Error: command\n", 15);
        free_command_array(cmd);
        return (NULL);
    }
    index++;

    i = 0;
    if (data.options != NULL)
    {
        while (data.options[i] != NULL)
        {
            cmd[index] = ft_strdup(data.options[i]);
            if (cmd[index] == NULL)
            {
                write(2, "Error: Failed to duplicate option\n", 34);
                free_command_array(cmd);
                return (NULL);
            }
            i++;
            index++;
        }
    }

    i = 0;
    if (data.arguments != NULL)
    {
        while (data.arguments[i] != NULL)
        {
            cmd[index] = ft_strdup(data.arguments[i]);
            if (cmd[index] == NULL)
            {
                write(2, "Error: Failed to duplicate argument\n", 36);
                free_command_array(cmd);
                return (NULL);
            }
            i++;
            index++;
        }
    }

    cmd[index] = NULL;
    return (cmd);
}


