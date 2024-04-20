/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:55:19 by iassil            #+#    #+#             */
/*   Updated: 2024/04/20 16:03:17 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	Utils function for the 'ft_check_syntax()' function
static int	ft_check_rest_syntax(t_token *head);

/*
*	This function checks the syntax of the line passed in the command line
*	if it's valid or not
*/
bool	ft_check_syntax(t_token *str)
{
	t_token	*head;

	head = str;
	if (head && head->type == PIPE)
		return (false);
	while (head != NULL)
	{
		if (!ft_check_quotes(head->token))
			return (false);
		else
		{
			if (ft_check_rest_syntax(head) == 1)
				return (false);
		}
		head = head->next;
	}
	return (true);
}

int	ft_check_within_brackets(char *str, t_brackets *c)
{
	while (str[c->i] && str[c->i] != '}')
	{
		if (str[c->i - 1] == '{' && !ft_isalpha(str[c->i]))
			c->c_left++;
		if (str[c->i] == '{' || ft_strchr(" \t\n\v\f\r", str[c->i])
			|| !ft_isalnum(str[c->i]))
			c->c_left++;
		c->i++;
	}
	if (str[c->i - 1] == '{' && str[c->i] == '}')
		return (1);
	if (str[c->i] && str[c->i] == '}')
		c->count++;
	if (c->c_left != 1)
		return (1);
	return (0);
}

int	ft_check_brackets(char *str)
{
	t_brackets	c;

	(1) && (c.i = 0, c.c = 0, c.c_left = 0, c.count = 0);
	while (str && str[c.i])
	{
		if (str[c.i] && c.i != 0 && str[c.i - 1] == '$' && str[c.i] == '{')
		{
			(1) && (c.count++, c.c_left++, c.c = str[c.i++]);
			if (ft_check_within_brackets(str, &c) == 1)
				return (1);
		}
		if (!str)
			break ;
		if (str[c.i])
			c.i++;
	}
	if (c.count % 2 == 0)
		return (0);
	return (1);
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
	if (ft_check_brackets(str) == 1)
		return (ft_error("msh: bad substitution\n"), 0);
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
	return (ft_error("msh: syntax error\n"), 0);
}

static int	ft_check_rest_syntax(t_token *head)
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
