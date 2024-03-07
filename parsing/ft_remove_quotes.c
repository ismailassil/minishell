/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:47:56 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 15:46:21 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *ft_allocate_for_the_string(char *str, int count)
{
	char	*ptr;
	int		i;
	int		j;
	int		c;

	(1) && (i = 0, j = 0, ptr = NULL, c = 0);
	ptr = (char *)malloc((ft_strlen(str) - count + 1) * sizeof(char));
	if (!ptr)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			c = str[i++];
		if (c == '\'' || c == '\"')
		{
			while (str[i] != c && str[i])
				ptr[j++] = str[i++];
			if (!str[i])
				break;
			if (str[i] == c)
				(i++, c = 0);
		}
		else
		{
			ptr[j++] = str[i++];
			if (!str[i])
				break;
		}
	}
	ptr[j] = '\0';
	return (ptr);
}

static char	*ft_trim_quotes(char *str)
{
	char	*ptr;
	int		count;
	int		i;
	int		c;

	(1) && (i = 0, count = 0, ptr = NULL, c = 0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			(1) && (c = str[i], count += 2, i++);
		if (c == '\'' || c == '\"')
		{
			while (str[i] != c && str[i])
				i++;
			if (str[i] == c)
				c = 0;
			if (!str[i])
				break;
		}
		i++;
	}
	ptr = ft_allocate_for_the_string(str, count);
	return (ptr);
}

// int	main() {
// 	printf("%s", ft_trim_quotes("l\"\"\'\'s"));
// }

static bool	ft_quotes_exists(char *s)
{
	char	*str;

	str = s;
	while (*str && str)
	{
		if (*str == '\'' || *str == '\"')
			return (true);
		str++;
	}
	return (false);
}

void	v(void)
{
	system("leaks minishell");
}

void	ft_remove_quotes(t_token **linked_list)
{
	t_token	*head;
	char	*tmp;

	// atexit(v);
	head = *linked_list;
	while (head)
	{
		if (ft_strchr(head->token, '$'))
			head = head->next;
		else
		{
			if (ft_quotes_exists(head->token) == true)
			{
				tmp = ft_trim_quotes(head->token);
				free(head->token);
				head->token = tmp;
			}
			head = head->next;
		}
	}
}
