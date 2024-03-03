/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:34:02 by iassil            #+#    #+#             */
/*   Updated: 2024/03/03 15:53:32 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	Checks if there is any space char	*/
bool	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

/*	Checks if there is any special char	*/
bool	ft_special_char(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

/*	Print the data in the Linked list imported from the shell	*/
void	ft_print(t_cont *lst)
{
	t_cont	*head;

	head = lst;
	while (head != NULL)
	{
		printf("====={%s}=====\n", head->holder);
		head = head->next;
	}
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
		else if (head->type == HEREDOC)
			printf(WHT"[HEREDOC]"RESET);
		else if (head->type == PIPE)
			printf(MAGENTA"[PIPE]"RESET);
		else if (head->type == ARG)
			printf("[ARG]");
		else
			printf("%s", head->token);
		head = head->next;
	}
}

/*	Add the input from shell to linked list	*/
void	ft_add_holder_to_container(t_cont	**spart, \
	char *input, int i, int index)
{
	char		*tmp;
	t_cont		*holder;

	tmp = ft_substr(input, i - index, index);
	holder = ft_lstnew(tmp);
	if (holder == NULL)
		exit(EXIT_FAILURE);
	ft_lstadd_back(spart, holder);
}
