/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 09:46:02 by iassil            #+#    #+#             */
/*   Updated: 2024/02/27 16:20:34 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_size;
	size_t	start;
	size_t	end;
	char	*ptr;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	s1_size = ft_strlen(s1);
	end = s1_size - 1;
	while (start < s1_size && ft_strchr(set, s1[start]))
		start++;
	while (end > 0 && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	else
		end = end - start + 1;
	ptr = ft_substr(s1, start, end);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}
