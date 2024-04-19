/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_v2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:35:39 by iassil            #+#    #+#             */
/*   Updated: 2024/04/18 15:04:26 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_free(char **big_ptr, size_t big_index)
{
	while (big_index--)
		free(big_ptr[big_index]);
	free(big_ptr);
	return (NULL);
}

static size_t	ft_count_words(char const *str, char *whitespaces)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (!ft_strchr(whitespaces, str[i])
			&& (ft_strchr(whitespaces, str[i + 1]) || str[i + 1] == '\0'))
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

static char	**ft_split_words(char **big_ptr, char const *str, char *whitespaces)
{
	size_t	i;
	size_t	index;
	size_t	big_index;

	i = 0;
	big_index = 0;
	while (str && str[i] != '\0')
	{
		index = 0;
		while (str[i] && ft_strchr(whitespaces, str[i]))
			i++;
		while (str[i] && !ft_strchr(whitespaces, str[i]) && str[i] != '\0')
		{
			index++;
			i++;
		}
		if (index > 0)
		{
			big_ptr[big_index++] = ft_substr(str, i - index, index);
			if (big_ptr[big_index - 1] == NULL)
				return (ft_free(big_ptr, big_index - 1));
		}
	}
	big_ptr[big_index] = 0;
	return (big_ptr);
}

char	**ft_split_v2(char const *s)
{
	size_t	nbr_of_words;
	char	**big_ptr;
	char	*whitespaces;

	whitespaces = " \t\n\v\f\r";
	if (s == NULL)
		return (NULL);
	nbr_of_words = ft_count_words(s, whitespaces) + 1;
	big_ptr = (char **)malloc(sizeof(char *) * nbr_of_words);
	if (big_ptr == NULL)
		return (NULL);
	big_ptr = ft_split_words(big_ptr, s, whitespaces);
	return (big_ptr);
}
