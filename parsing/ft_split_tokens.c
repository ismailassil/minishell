/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 20:15:25 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 21:03:26 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	
*	This function allocates for the string from which it should
*	the whitespaces
*	[""ls'' "-"a'l'] => [{""ls''}, {"-"a'l'}]
*/
static void	ft_add_to_linked_list(t_token **head, char *str, int start, int end)
{
	char	*ptr;

	ptr = ft_substr(str, start, end - start);
	if (!ptr)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
	ft_push_token(ptr, head);
	free(ptr);
}

/*	
*	After inserting spaces between operators [>|<] 
*	This function splits the between the whitespaces
*	Like: [""ls'' "-"a'l']
*/
void	ft_split_tokens(t_token **head, char *str)
{
	int		quote;
	t_c		c;

	(1) && (c.i = 0, c.j = 0, quote = 0);
	while (str && str[c.i])
	{
		while (str[c.i] && ft_strchr(" \t\n\v\f\r", str[c.i]))
			c.i++;
		c.j = c.i;
		while (str[c.i] && !ft_strchr(" \t\n\v\f\r", str[c.i]))
		{
			if (str[c.i] && (str[c.i] == '\"' || str[c.i] == '\''))
			{
				quote = str[c.i++];
				while (str[c.i] && str[c.i] != quote)
					c.i++;
				if (str[c.i] == quote)
					quote = 0;
			}
			c.i++;
		}
		ft_add_to_linked_list(head, str, c.j, c.i);
		if (!str[c.i])
			break ;
	}
}
