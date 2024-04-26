/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_v3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:54:15 by iassil            #+#    #+#             */
/*   Updated: 2024/04/26 11:53:58 by iassil           ###   ########.fr       */
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
	int		quote;
	int		flag;

	(1) && (i = 0, count = 0, quote = 0, flag = 0);
	while (str && str[i] != '\0')
	{
		if (str[i] == SQ)
		{
			(1) && (quote = str[i], flag = 1, i++);
			while (flag == 1 && str[i] != quote && str[i] != '\0')
				i++;
			if (flag == 1 && str[i] == quote)
				(1) && (flag = 0, i++);
			count++;
		}
		if (str[i] && !ft_strchr(whitespaces, str[i])
			&& (ft_strchr(whitespaces, str[i + 1]) || str[i + 1] == '\0'))
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

void	ft_indexing(char const *str, size_t *i, size_t *index, \
	char *whitespaces)
{
	int	quote;
	int	flag;

	(1) && (quote = 0, flag = 0);
	while (str && str[*i] && !ft_strchr(whitespaces, str[*i]))
	{
		if (str[*i] && str[*i] == SQ)
		{
			(1) && (quote = str[*i], flag = 1, (*i)++, (*index)++);
			while (flag == 1 && str[*i] != quote && str[*i] != '\0')
				(1) && ((*index)++, (*i)++);
			if (flag == 1 && str[*i] == quote)
				(1) && (flag = 0, (*i)++, (*index)++);
		}
		if (str[*i] && !ft_strchr(whitespaces, str[*i]))
			(1) && ((*index)++, (*i)++);
	}
}

static char	**ft_split_words(char **big_ptr, char const *str, \
	char *whitespaces)
{
	size_t	i;
	size_t	index;
	size_t	big_index;

	(1) && (i = 0, big_index = 0);
	while (str && str[i] != '\0')
	{
		index = 0;
		while (str[i] && ft_strchr(whitespaces, str[i]))
			i++;
		if (str[i] && !ft_strchr(whitespaces, str[i]))
			ft_indexing(str, &i, &index, whitespaces);
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

char	**ft_split_vquote(char const *s)
{
	size_t	nbr_of_words;
	char	**big_ptr;
	char	*whitespaces;

	if (!s)
		return (NULL);
	whitespaces = " \t\n\v\f\r";
	nbr_of_words = ft_count_words(s, whitespaces) + 1;
	big_ptr = (char **)malloc(sizeof(char *) * nbr_of_words);
	ft_check_allocation(big_ptr);
	big_ptr = ft_split_words(big_ptr, s, whitespaces);
	return (big_ptr);
}
