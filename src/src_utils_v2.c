/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src_utils_v2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:34:02 by iassil            #+#    #+#             */
/*   Updated: 2024/04/04 00:14:33 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*	Print the data in the Linked list imported from the shell	*/
void	ft_print(t_token *lst)
{
	t_token	*head;

	head = lst;
	printf("\n");
	while (head != NULL)
	{
		printf(WHT"=={[%d]%s}=="RESET, head->is_var, head->token);
		head = head->next;
	}
	printf("\n");
}

void	ft_print_outfile_and_here_doc(t_cont *container)
{
	int	i;

	i = 0;
	while (container->outfile[i] != 0)
	{
		if (container->outfile_type[i] == 1)
			printf("OUTFILE[%d] = %s\n", i, container->outfile[i]);
		else if (container->outfile_type[i] == 2)
			printf("APPEND[%d] = %s\n", i, container->outfile[i]);
		i++;
	}
	i = 0;
	while (container->here_doc[i] != 0)
		(1) && (printf("HEREDOC[%d] = %s\n", \
			i, container->here_doc[i]), i++);
}

void	ft_print_container(t_cont *head)
{
	int		i;
	t_cont	*container;

	(1) && (i = 0, container = head);
	printf("\n");
	while (container != NULL)
	{
		printf("CMD = %s\n", container->cmd);
		i = 0;
		while (container->arg[i] != 0)
			(1) && (printf("ARG[%d] = %s\n", i, container->arg[i]), i++);
		i = 0;
		while (container->infile[i] != 0)
			(1) && (printf("INFILE[%d] = %s\n", i, container->infile[i]), i++);
		ft_print_outfile_and_here_doc(container);
		container = container->next;
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
