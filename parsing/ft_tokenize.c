/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-che <aibn-che@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:05:24 by iassil            #+#    #+#             */
/*   Updated: 2024/04/25 18:45:50 by aibn-che         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	Utils functions for the 'ft_tokenize()' function
static void	ft_check_rest_of_else(t_token *head, int *flag);
static void	ft_check_else(t_token *head, int *flag, int *index);

/*
*	This function tokenize the node
*	{ from their position if they are CMDs ARGs PIPE ... }
*	like:	[ls -al > file		|		grep pipex < file2]
*			CMD ARG OUTFILE	   PIPE		CMD   ARG    INFILE
*	index : refer to the order of a certain file
*	flag  : if [== 1] means that the cmd is found and the following
*			is ARG or FILENAME or HEREDOC
*			if [== 0] the cmd has not been found
*/
void	ft_tokenize(t_token **str)
{
	t_tokenize	t;
	t_token		*node;

	(1) && (t.i = 0, t.flag = 0, t.head = *str, t.index = 0);
	while (t.head != NULL)
	{
		node = t.head->next;
		if (ft_strncmp(t.head->token, ">", ft_strlen(t.head->token)) == 0)
		{
			if (node != NULL)
				(1) && (node->type = FILENAME, node->findex = t.index++);
			t.head->type = OUTFILE;
		}
		else if (ft_strncmp(t.head->token, "<", ft_strlen(t.head->token)) == 0)
		{
			if (node != NULL)
				(1) && (node->type = FILENAME, node->findex = t.index++);
			t.head->type = INFILE;
		}
		else
			ft_check_else(t.head, &t.flag, &t.index);
		t.head = t.head->next;
	}
}

static void	ft_check_else(t_token *head, int *flag, int *index)
{
	if (ft_strncmp(head->token, ">>", ft_strlen(head->token)) == 0)
	{
		if (head->next != NULL)
		{
			head->next->type = FILENAME;
			head->next->findex = (*index)++;
		}
		head->type = APPEND;
	}
	else if (ft_strncmp(head->token, "<<", ft_strlen(head->token)) == 0)
	{
		if (head->next != NULL)
			head->next->type = DELIMITER;
		head->type = HEREDOC;
	}
	else if (ft_strncmp(head->token, "|", ft_strlen(head->token)) == 0)
		(1) && (head->type = PIPE, *flag = 0, *index = 0);
	else
		ft_check_rest_of_else(head, flag);
}

static void	ft_check_rest_of_else(t_token *head, int *flag)
{
	if (head->type == FILENAME || head->type == DELIMITER || head->type == ARG)
	{
		if (*flag == 1 && head->type == FILENAME && head->next != NULL)
			head->next->type = ARG;
		if (*flag == 1 && head->type == DELIMITER && head->next != NULL)
			head->next->type = ARG;
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
