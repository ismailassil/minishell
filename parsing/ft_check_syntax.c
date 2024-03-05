/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:55:19 by iassil            #+#    #+#             */
/*   Updated: 2024/03/05 11:07:27 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_quotes(char *str)
{
	int	i[2];
	int	count_quotes;

	i[0] = 0;
	count_quotes = 0;
	while (str[i[0]] != '\0')
	{
		if (str[i[0]] == '\'' || str[i[0]] == '\"')
		{
			count_quotes++;
			i[1] = str[i[0]++];
			while (str[i[0]] != '\0')
			{
				if (i[1] == str[i[0]])
					count_quotes++;
				i[0]++;
			}
			if (str[i[0]] == '\0')
				break ;
		}
		i[0]++;
	}
	if ((count_quotes % 2) == 0)
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

void	ft_check_syntax(t_token *str)
{
	t_token	*head;

	head = str;
	if (head->type == PIPE)
	{
		ft_error();
		return ;
	}
	while (head != NULL)
	{
		if (!check_quotes(head->token))
		{
			ft_error();
			break ;
		}
		else
			if (ft_check_rest(head) == 1)
				break ;
		head = head->next;
	}
}
