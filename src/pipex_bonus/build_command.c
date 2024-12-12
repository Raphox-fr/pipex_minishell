/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:02:21 by raphox            #+#    #+#             */
/*   Updated: 2024/12/10 16:37:16 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char **split_options(char *options, int *option_count)
{
    char **split_command;
    int j;

    split_command = NULL;
    j = 0;
    if (options)
    {
        split_command = ft_split(options, ' ');
        if (!split_command)
            return (NULL);
        while (split_command[j])
            j++;
    }
    *option_count = j;
    return (split_command);
}

/**
 * Allocate memory for the command array.
 */
char **allocate_command(int option_count, int nbr_args)
{
    char **cmd;

    cmd = malloc((option_count + nbr_args + 2) * sizeof(char *));
    if (!cmd)
        return (NULL);
    return (cmd);
}

/**
 * Copy the command to the first element of the command array.
 */
int copy_command(char **cmd, char *command)
{
	int i;
	int found;
	i = 0;

	found = 0;

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
			return (0);
		}
		cmd[0] = ft_strdup(command + found);
	}
	else 
		cmd[0] = ft_strdup(command);
    if (!cmd[0])
        return (0);
    return (1);
}

/**
 * Copy options into the command array.
 */
int copy_options(char **cmd, char **split_command, int i, int option_count)
{
    int k;

    k = 0;
    while (k < option_count)
    {
        cmd[i] = ft_strdup(split_command[k]);
        if (!cmd[i])
        {
            free_command(cmd); // Assurez-vous de libérer en cas d'échec.
            return (0);
        }
        i++;
        k++;
    }
    free_command(split_command); // Libération après utilisation.
    return (1);
}

/**
 * Copy arguments into the command array.
 */
int copy_arguments(char **cmd, char **arguments, int i, int nbr_args)
{
    int k;

    k = 0;
    while (k < nbr_args)
    {
        cmd[i] = ft_strdup(arguments[k]);
        if (!cmd[i])
        {
            free_command(cmd);
            return (0);
        }
        i++;
        k++;
    }
    return (1);
}

/**
 * Join options into a single string.
 */
char *join_options(char **options)
{
    int i;
    char *result;
    char *temp;

    i = 0;
    result = ft_strdup("");
    if (options != NULL)
    {
        free(result);
        result = ft_strdup(options[0]);
        i = 1;
        while (options[i] != NULL)
        {
            temp = ft_strjoin(result, options[i], 1); 
            free(result);
            result = temp;
            i++;
        }
    }
    return (result); // L'appelant doit libérer.
}

/**
 * Initialize the command array with the command and options.
 */
char **initialize_command(char *command, char **split_command, int option_count, int nbr_args)
{
    char **cmd;

    cmd = allocate_command(option_count, nbr_args);
    
	if (!cmd)
    {
        if (split_command)
            free_command(split_command);
        return (NULL);
    }
    if (!copy_command(cmd, command))
    {
        free_command(split_command);
        free_command(cmd);
        return (NULL);
    }
    return (cmd);
}

/**
 * Build the full command array.
 */
char **build_command(t_data_rule data)
{
    char **cmd;
    char **split_command;
    char *string_options;
    int option_count;
    int i;

    string_options = join_options(data.options);
    if (!string_options)
        return (NULL);

    split_command = split_options(string_options, &option_count);
    free(string_options); // Libération après utilisation.

    if (data.options && !split_command)
        return (NULL);

    cmd = initialize_command(data.command, split_command, option_count, data.nbr_args);
    if (!cmd)
        return (NULL);

    i = 1;
    if (split_command && !copy_options(cmd, split_command, i, option_count))
    {
        free_command(cmd);
        return (NULL);
    }
    if (data.options != NULL)
        i = option_count + 1;

    if (!copy_arguments(cmd, data.arguments, i, data.nbr_args))
    {
        free_command(cmd);
        return (NULL);
    }

    cmd[i + data.nbr_args] = NULL;
    return (cmd);
}

