/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphox <raphox@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:37:08 by thodos-s          #+#    #+#             */
/*   Updated: 2024/10/11 17:16:53 by raphox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int space)
{
	size_t		i;
	size_t		k;
	char		*dest;

	i = 0;
	k = 0;
	/*if (!s1 || !s2)
		return (NULL);*/
	dest = malloc(sizeof(char) * (ft_strlen((char *)s1 + 1) + \
				ft_strlen((char *)s2) + 2 + space));
	if (!dest)
		return (NULL);
	while (s1[i])
		dest[k++] = s1[i++];
	if (space == 1)
	{
		dest[k] = ' ';
		k++;
	}
	i = 0;
	while (s2[i])
		dest[k++] = s2[i++];
	dest[k] = '\0';
	return (dest);
}
