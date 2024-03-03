/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 14:55:19 by iassil            #+#    #+#             */
/*   Updated: 2024/03/03 15:21:31 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_error(void)
{
	perror("msh: parse error");
}

void	ft_check_syntax(t_token *str)
{
	t_token	*head;

	head = str;
	while (head != NULL)
	{
		if (head->next != NULL
			&& (head->type == INFILE || head->type == OUTFILE
			|| head->type == APPEND || head->type == HEREDOC)
			&& (head->next->type == INFILE || head->next->type == OUTFILE
			|| head->next->type == APPEND || head->next->type == HEREDOC))
		{
			ft_error();
			break ;
		}
		else if (head->next == NULL
			&& (head->type == PIPE || head->type == INFILE
			|| head->type == OUTFILE || head->type == APPEND
			|| head->type == HEREDOC))
		{
			ft_error();
			break ;
		}
		head = head->next;
	}
}
