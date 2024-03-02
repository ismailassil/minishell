/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:28:28 by aibn-che          #+#    #+#             */
/*   Updated: 2024/02/29 15:35:53 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	quote = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if(str[i] == 39)
		{
			i++;
			count++;
			while (str[i] && str[i] != 39)
				i++;
		}
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (!(str[i] == c) && str[i])
				i++;
		}
	}
	return (count);
}

static char	*ft_strdupp(const char *s1, char c, int *index)
{
	int		i;
	char	*dup;
	int		len;
	int		start;

	if (!s1)
		return (NULL);
	len = 0;
	while (s1[*index] == c)
		(*index)++;
	start = *index;
	while (s1[start] != c && s1[start])
	{
		len++;
		start++;
	}
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	i = 0;
	while (i < len)
		dup[i++] = s1[(*index)++];
	dup[i] = '\0';
	return (dup);
}

static char	*free_arr(char **arr, int i)
{
	if (!arr)
		return (NULL);
	while (i >= 0)
		free(arr[i--]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		c_word;
	int		index;
	int		i;
	char	**arr;

	if (!s)
		return (NULL);
	c_word = count_words(s, c);
	index = 0;
	i = 0;
	arr = (char **)malloc(sizeof(char *) * (c_word + 1));
	if (!arr)
		return (NULL);
	while (c_word)
	{
		arr[i] = ft_strdupp(s, c, &index);
		if (!arr[i])
			return ((char **)free_arr(arr, i));
		c_word--;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
