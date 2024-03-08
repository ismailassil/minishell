/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:05:24 by iassil            #+#    #+#             */
/*   Updated: 2024/03/07 20:57:38 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	Utils functions for the 'ft_tokenize()' function
static void	ft_check_rest_of_else(t_token *head, int *flag);
static void	ft_check_else(t_token *head, int *flag);

/*
*	This function tokenize the node
*	{ from their position if they are CMDs ARGs PIPE ... }
*	like:	[ls -al > file		|		grep pipex < file2]
*			CMD ARG OUTFILE	   PIPE		CMD   ARG    INFILE
*/
void	ft_tokenize(t_token **str)
{
	t_token	*head;
	int		flag;
	int		i;

	i = 0;
	head = *str;
	flag = 0;
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
			ft_check_else(head, &flag);
		head = head->next;
	}
}

static void	ft_check_rest_of_else(t_token *head, int *flag)
{
	if (head->type == FILENAME || head->type == DELIMITER || head->type == ARG)
	{
		if (*flag == 1 && head->type == FILENAME && head->next != NULL)
			(1) && (head->next->type = ARG, *flag = 0);
		if (head->type == ARG && head->next != NULL)
			head->next->type = ARG;
		else if (head->type != ARG
			&& head->next != NULL && head->next->type != ARG)
			head->next->type = CMD;
	}
	else
	{
		(1) && (head->type = CMD, *flag = 1);
		if (head->next != NULL)
			head->next->type = ARG;
	}
}

static void	ft_check_else(t_token *head, int *flag)
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
		(1) && (head->type = HEREDOC, *flag = 0);
	}
	else if (ft_strncmp(head->token, "|", ft_strlen(head->token)) == 0)
		(1) && (head->type = PIPE, *flag = 0);
	else
		ft_check_rest_of_else(head, flag);
}
