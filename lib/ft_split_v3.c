/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_v3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 14:54:15 by iassil            #+#    #+#             */
/*   Updated: 2024/04/18 15:53:00 by iassil           ###   ########.fr       */
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

static size_t	ft_count_words(char const *str, char c)
{
	size_t	i;
	size_t	count;
	int		quote;
	int		flag;

	(1) && (i = 0, count = 0, quote = 0, flag = 0);
	while (str && str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			(1) && (quote = str[i], flag = 1, i++);
			while (flag == 1 && str[i] != quote && str[i] != '\0')
				i++;
			if (flag == 1 && str[i] == quote)
				(1) && (flag = 0, i++);
			count++;
		}
		if (str[i] && str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

void	ft_indexing(char const *str, size_t *i, size_t *index, char c)
{
	int	quote;
	int	flag;

	(1) && (quote = 0, flag = 0);
	if ((str[*i] == '"' || str[*i] == '\''))
	{
		(1) && (quote = str[*i], flag = 1, (*i)++, (*index)++);
		while (flag == 1 && str[*i] != quote && str[*i] != '\0')
			(1) && ((*index)++, (*i)++);
		if (flag == 1 && str[*i] == quote)
			(1) && (flag = 0, (*i)++, (*index)++);
	}
	else
		while (str[*i] != c && str[*i] != '\0')
			(1) && ((*index)++, (*i)++);
}

static char	**ft_split_words(char **big_ptr, char const *str, char c)
{
	size_t	i;
	size_t	index;
	size_t	big_index;

	(1) && (i = 0, big_index = 0);
	while (str && str[i] != '\0')
	{
		index = 0;
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\0')
			ft_indexing(str, &i, &index, c);
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

char	**ft_split_vquote(char const *s, char c)
{
	size_t	nbr_of_words;
	char	**big_ptr;

	if (!s)
		return (NULL);
	nbr_of_words = ft_count_words(s, c) + 1;
	big_ptr = (char **)malloc(sizeof(char *) * nbr_of_words);
	if (big_ptr == NULL)
		return (NULL);
	big_ptr = ft_split_words(big_ptr, s, c);
	return (big_ptr);
}
