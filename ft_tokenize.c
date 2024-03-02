/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:05:24 by iassil            #+#    #+#             */
/*   Updated: 2024/03/02 22:09:55 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	ft_check_next(t_token *head)
{
	// if (head->type == CMD)
	// {
	// 	if (ft_strncmp(head->token, ">", ft_strlen(head->token)) != 0
	// 		&& ft_strncmp(head->token, "<", ft_strlen(head->token)) != 0
	// 		&& ft_strncmp(head->token, ">>", ft_strlen(head->token)) != 0
	// 		&& ft_strncmp(head->token, "|", ft_strlen(head->token)) != 0
	// 		&& ft_strncmp(head->token, "<<", ft_strlen(head->token)) != 0)
	// 		head->next->type = ARG;
	// }
	// else
	if (head == NULL)
		(write(2, "msh: parse error\n", 17), exit(EXIT_FAILURE));
}

void	ft_tokenize(t_token **str)
{
	t_token	*head;

	head = *str;
	while (head != NULL)
	{
		printf("%s, %d\n", head->token, head->type);
		if (strncmp(head->token, ">", ft_strlen(head->token)))
		{
			if (head->next != NULL)
				head->next->type = FILENAME;
			head->type = OUTFILE;
		}
		else if (strncmp(head->token, "<", ft_strlen(head->token)))
		{
			if (head->next != NULL)
				head->next->type = FILENAME;
			head->type = INFILE;
		}
		else if (strncmp(head->token, ">>", ft_strlen(head->token)))
		{
			if (head->next != NULL)
				head->next->type = FILENAME;
			head->type = APPEND;
		}
		else if (strncmp(head->token, "<<", ft_strlen(head->token)))
		{
			if (head->next != NULL)
				head->next->type = DELIMITER;
			head->type = HEREDOC;
		}
		else if (strncmp(head->token, "|", ft_strlen(head->token)))
			head->type = PIPE;
		else
		{
			// ft_check_next(head);
			head->type = CMD;
		}
		head = head->next;
	}
}
