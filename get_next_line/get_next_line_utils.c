/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:52:23 by aibn-che          #+#    #+#             */
/*   Updated: 2023/12/29 18:36:16 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	str_lenn(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*str_join(char **s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;
	int		j;

	j = 0;
	i = 0;
	len1 = str_lenn(*s1);
	len2 = str_lenn(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (free(*s1), *s1 = NULL, NULL);
	while (*s1 && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	while (s2 && s2[j] && i < len1 + len2)
		str[i++] = s2[j++];
	free(*s1);
	*s1 = NULL;
	str[i] = '\0';
	return (str);
}

int	encounter_space(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i++] == '\n')
			return (1);
	}
	return (0);
}

char	*substring(char *s, int index)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (index + 2));
	if (!str)
		return (NULL);
	while (s && s[i] && i <= index)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	handle_nl(char **container, char *buffer, char **keeper)
{
	int		i;
	char	*sub;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			*keeper = substring(buffer + (i + 1), str_lenn(buffer + (i + 1)));
			if (str_lenn(*keeper) == 0)
				(free(*keeper), *keeper = NULL);
			sub = substring(buffer, i);
			*container = str_join(container, sub);
			if (!*container)
				(free(*keeper), *keeper = NULL);
			(free(sub), sub = NULL);
			break ;
		}
		i++;
	}
}
