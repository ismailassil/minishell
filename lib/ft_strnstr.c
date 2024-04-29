/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:55:49 by iassil            #+#    #+#             */
/*   Updated: 2024/04/02 16:58:25 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *str, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	index;

	i = 0;
	if (str == NULL && len == 0)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		index = i;
		while (str[index] == needle[j] && needle[j] != '\0' && index < len)
		{
			if (index > len)
				return (NULL);
			if (needle[j + 1] == '\0')
				return ((char *)&str[i]);
			j++;
			index++;
		}
		i++;
	}
	return (0);
}
