/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:02:21 by raphox            #+#    #+#             */
/*   Updated: 2024/11/26 15:33:02 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**split_options(char *options, int *option_count)
{
	char	**split_command;
	int		j;

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

char	**allocate_command(int option_count, int nbr_args)
{
	char	**cmd;

	cmd = malloc((option_count + nbr_args + 2) * sizeof(char *));
	if (!cmd)
		return (NULL);
	return (cmd);
}

int	copy_command(char **cmd, char *command)
{
	cmd[0] = ft_strdup(command);
	if (!cmd[0])
		return (0);
	return (1);
}

int	copy_options(char **cmd, char **split_command, int i, int option_count)
{
	int k;

	k = 0;
	while (k < option_count)
	{
		cmd[i] = ft_strdup(split_command[k]);
		if (!cmd[i])
			return (0);
		i++;
		k++;
	}
	free_command(split_command);
	return (1);
}

int	copy_arguments(char **cmd, char **arguments, int i, int nbr_args)
{
	int k;

	k = 0;
	while (k < nbr_args)
	{
		cmd[i] = ft_strdup(arguments[k]);
		if (!cmd[i])
			return (0);
		i++;
		k++;
	}
	return (1);
}


char	**initialize_command(char *command, char **split_command, int option_count, int nbr_args)
{
	char	**cmd;

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
	else
		return (NULL);
	return (result);
	free(result);
}


char	**build_command(t_data_rule data)
{
	char	**cmd;
	char	**split_command;
	char	*string_options;
	int		option_count;
	int		i;

	string_options = join_options(data.options);
	// write(2, string_options, ft_strlen(string_options));
	split_command = split_options(string_options, &option_count);
	if (data.options && !split_command)
		return (NULL);
	cmd = initialize_command(data.command, split_command, option_count, data.nbr_args);
	if (!cmd)
		return (NULL);
	i = 1;
	if (split_command && !copy_options(cmd, split_command, i, option_count))
	{
		free(string_options);
		free_command(cmd);
		return (NULL);
	}
	if (data.options != NULL)
		i = option_count + 1;
	if (!copy_arguments(cmd, data.arguments, i, data.nbr_args))
	{
		free(string_options);
		free_command(cmd);
		return (NULL);
	}
	cmd[i + data.nbr_args] = NULL;
	return (cmd);
}
