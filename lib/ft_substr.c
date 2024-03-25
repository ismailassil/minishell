/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:00:23 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 21:11:50 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	slen;

	if (!s)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		return (ft_strdup(""));
	str = (char *)(s + start);
	slen = ft_strlen(str);
	if (slen > len)
		slen = len;
	i = 0;
	str = (char *)malloc((slen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (slen)
	{
		((char *)str)[i++] = s[start];
		start++;
		slen--;
	}
	((char *)str)[i] = '\0';
	return ((char *)str);
}
