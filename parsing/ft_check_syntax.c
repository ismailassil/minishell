/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:55:19 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 22:18:25 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_quotes(char *str)
{
	int	i;
	int	c;
	int	count;

	i = 0;
	c = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
		{
			count++;
			c = str[i++]; 
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

static void	ft_error(void)
{
	write(2, "msh: parse error\n", 17);
}

static int	ft_check_rest(t_token *head)
{
	if (head->next != NULL
		&& (head->type == INFILE || head->type == OUTFILE
			|| head->type == APPEND || head->type == HEREDOC)
		&& (head->next->type == INFILE || head->next->type == OUTFILE
			|| head->next->type == APPEND || head->next->type == HEREDOC))
		return (ft_error(), 1);
	else if (head->next == NULL
		&& (head->type == PIPE || head->type == INFILE
			|| head->type == OUTFILE || head->type == APPEND
			|| head->type == HEREDOC))
		return (ft_error(), 1);
	return (0);
}

bool	ft_check_syntax(t_token *str)
{
	t_token	*head;

	head = str;
	if (head && head->type == PIPE)
		return (ft_error(), false);
	while (head != NULL)
	{
		if (!check_quotes(head->token))
			return (ft_error(), false);
		else
			if (ft_check_rest(head) == 1)
				return (ft_error(), false);
		head = head->next;
	}
	return (true);
}
