/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:34:02 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 14:13:17 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Checks if a char is a special character or not				*/
int	ft_check_if_chars_digit(int c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

/*	Print the data in the Linked list imported from the shell	*/
void	ft_print(t_token *lst)
{
	t_token	*head;

	head = lst;
	printf("\n");
	while (head != NULL)
	{
		printf(WHT"=={%s}=="RESET, head->token);
		head = head->next;
	}
}

static void	ft_else_print(t_token *head)
{
	if (head->type == HEREDOC)
		printf(WHT"[HEREDOC]"RESET);
	else if (head->type == PIPE)
		printf(MAGENTA"[PIPE]"RESET);
	else if (head->type == ARG)
		printf("[ARG]");
	else
		printf("%s", head->token);
}

void	ft_print_types(t_token *str)
{
	t_token	*head;

	head = str;
	while (head != NULL)
	{
		if (head->type == CMD)
			printf(RED"[CMD]"RESET);
		else if (head->type == OUTFILE)
			printf(GREEN"[OUTFILE]"RESET);
		else if (head->type == INFILE)
			printf(YELLOW"[INFILE]"RESET);
		else if (head->type == APPEND)
			printf(BLUE"[APPEND]"RESET);
		else if (head->type == FILENAME)
			printf(MAGENTA"[FILENAME]"RESET);
		else if (head->type == DELIMITER)
			printf(CYAN"[DELIMITER]"RESET);
		else
			ft_else_print(head);
		head = head->next;
	}
}
