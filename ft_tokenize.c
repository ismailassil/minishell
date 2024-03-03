/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:05:24 by iassil            #+#    #+#             */
/*   Updated: 2024/03/03 14:53:28 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_check_rest_of_else(t_token *head)
{
	if (head->type == FILENAME || head->type == DELIMITER || head->type == ARG)
	{
		if (head->type == ARG && head->next != NULL)
			head->next->type = ARG;
		else if (head->type != ARG && head->next != NULL)
			head->next->type = CMD;
	}
	else
	{
		head->type = CMD;
		if (head->next != NULL)
			head->next->type = ARG;
	}
}

static void	ft_check_else(t_token *head)
{
	if (ft_strncmp(head->token, ">>", ft_strlen(head->token)) == 0)
	{
		if (head->next != NULL)
			head->next->type = FILENAME;
		head->type = APPEND;
	}
	else if (ft_strncmp(head->token, "<<", ft_strlen(head->token)) == 0)
	{
		if (head->next != NULL)
			head->next->type = DELIMITER;
		head->type = HEREDOC;
	}
	else if (ft_strncmp(head->token, "|", ft_strlen(head->token)) == 0)
		head->type = PIPE;
	else
		ft_check_rest_of_else(head);
}

void	ft_tokenize(t_token **str)
{
	t_token	*head;
	int		i;

	i = 0;
	head = *str;
	while (head != NULL)
	{
		if (ft_strncmp(head->token, ">", ft_strlen(head->token)) == 0)
		{
			if (head->next != NULL)
				head->next->type = FILENAME;
			head->type = OUTFILE;
		}
		else if (ft_strncmp(head->token, "<", ft_strlen(head->token)) == 0)
		{
			if (head->next != NULL)
				head->next->type = FILENAME;
			head->type = INFILE;
		}
		else
			ft_check_else(head);
		head = head->next;
	}
}
