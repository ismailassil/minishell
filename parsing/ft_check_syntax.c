/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:55:19 by iassil            #+#    #+#             */
/*   Updated: 2024/03/17 22:19:56 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	Utils function for the 'ft_check_syntax()' function
static int	ft_check_rest(t_token *head);

/*
*	This function checks the syntax of the line passed in the command line
*	if it's valid or not
*/
bool	ft_check_syntax(t_token *str)
{
	t_token	*head;

	head = str;
	if (head && head->type == PIPE)
		return (ft_error("\n"), false);
	while (head != NULL)
	{
		if (!ft_check_quotes(head->token))
			return (ft_error("msh: parse error\n"), false);
		else
		{
			if (ft_check_rest(head) == 1)
				return (ft_error("msh: parse error\n"), false);
		}
		head = head->next;
	}
	return (true);
}

/*
*	This function checks the syntax of quotes if they are valid or not!
*/
int	ft_check_quotes(char *str)
{
	int	i;
	int	c;
	int	count;

	(1) && (i = 0, c = 0, count = 0);
	while (str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			(1) && (count++, c = str[i++]);
			while (str[i] && str[i] != c)
				i++;
			if (str[i] && str[i] == c)
				count++;
		}
		if (!str[i])
			break ;
		i++;
	}
	if ((count % 2) == 0)
		return (1);
	return (0);
}

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
}

static int	ft_check_rest(t_token *head)
{
	if (head->next != NULL
		&& (head->type == INFILE || head->type == OUTFILE
			|| head->type == APPEND || head->type == HEREDOC)
		&& (head->next->type == INFILE || head->next->type == OUTFILE
			|| head->next->type == APPEND || head->next->type == HEREDOC))
		return (1);
	else if (head->next == NULL
		&& (head->type == PIPE || head->type == INFILE
			|| head->type == OUTFILE || head->type == APPEND
			|| head->type == HEREDOC))
		return (1);
	return (0);
}
