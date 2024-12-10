/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thodos-s <thodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:59:15 by thodos-s          #+#    #+#             */
/*   Updated: 2023/12/03 15:17:24 by thodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *source)
{
	char	*array;
	size_t	i;

	i = 0;
	array = NULL;
	array = (char *)malloc(ft_strlen((char *)source) + 1);
	if (!array)
		return (NULL);
	while (source[i])
	{
		array[i] = source[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
