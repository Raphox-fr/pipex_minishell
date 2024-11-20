/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_syntax_tool.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:23:54 by thodos-s          #+#    #+#             */
/*   Updated: 2024/11/20 12:23:55 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Parsing.h"

int	empty_braquet(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '(')
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == ')')
		return (1);
	return (0);
}
