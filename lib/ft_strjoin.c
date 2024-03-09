/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 21:32:43 by iassil            #+#    #+#             */
/*   Updated: 2024/03/08 16:31:03 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_check(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	else if (s2 == NULL)
		return ((char *)s1);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;

	if (s1 == NULL || s2 == NULL)
		return (ft_check(s1, s2));
	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ptr = (char *)malloc(s1_len + s2_len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < s1_len)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (j < s2_len)
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin_(char *str1, char *str2)
{
	int		len1;
	int		len2;
	char	*new_str;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	(1) && (len1 = ft_strlen(str1), len2 = ft_strlen(str2));
	new_str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
	while (str1 && str1[i])
	{
		new_str[i] = str1[i];
		i++;
	}
	while (str2 && str2[j])
	{
		new_str[i] = str2[j];
		(1) && (i++, j++);
	}
	new_str[i] = '\0';
	return (new_str);
}
