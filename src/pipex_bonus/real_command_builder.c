/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_command_builder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 17:14:05 by raphox            #+#    #+#             */
/*   Updated: 2024/12/10 22:08:15 by raphox           ###   ########.fr       */
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
		return(0); 
	}

	while (options[i] != NULL)
		i++;
	*option_count = i;
}



char **build_command(t_data_rule data)
{
	int index;
	int i;

	
	char **cmd;
	int options_count;

	count_options(data.options, &options_count);
	index = 0;
	i = 0;
	
	cmd = malloc(sizeof(char *) * (1 + options_count + data.nbr_args + 1));
	if (cmd == NULL)
		return (NULL);

		

	cmd[index] = ft_strdup(data.command);
	index++;
	
	if (data.options != NULL)
	{
		while (data.options[i] != NULL)
		{
			cmd[index] = ft_strdup(data.options[i]);
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
			i++;
			index++;
		}
	}
	cmd[index] = NULL;
	return (cmd);
}

