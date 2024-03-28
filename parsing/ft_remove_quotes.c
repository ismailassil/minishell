/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:47:56 by iassil            #+#    #+#             */
/*   Updated: 2024/03/28 02:08:41 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_fill_ptr(char *str, char **ptr)
{
	t_c		c;

	(1) && (c.i = 0, c.j = 0, c.quote = 0);
	while (str[c.i])
	{
		if (str[c.i] == '\'' || str[c.i] == '\"')
			c.quote = str[c.i++];
		if (c.quote == '\'' || c.quote == '\"')
		{
			while (str[c.i] != c.quote && str[c.i])
				(*ptr)[c.j++] = str[c.i++];
			if (!str[c.i])
				break ;
			if (str[c.i] == c.quote)
				(1) && (c.i++, c.quote = 0);
		}
		else
		{
			(*ptr)[c.j++] = str[c.i++];
			if (!str[c.i])
				break ;
		}
	}
	(*ptr)[c.j] = '\0';
}

static char	*ft_allocate_for_the_string(char *str, int count)
{
	char	*ptr;

	ptr = (char *)malloc((ft_strlen(str) - count + 1) * sizeof(char));
	if (!ptr)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	ft_fill_ptr(str, &ptr);
	return (ptr);
}

char	*ft_trim_quotes(char *str)
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
				break ;
		}
		i++;
	}
	ptr = ft_allocate_for_the_string(str, count);
	return (ptr);
}

/*
*	Checks if quotes exists in the string
*/
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

/*
*	This function removes quotes from the nodes that have them
*	and does not remove quotes from node that
*	have '$' {nodes need to be expanded}
*/
void	ft_remove_quotes(t_token **linked_list)
{
	t_token	*head;
	char	*tmp;

	head = *linked_list;
	while (head)
	{
		if (ft_strchr(head->token, '$') || head->type == DELIMITER)
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
