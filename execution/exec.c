/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/06 21:11:26 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//	create a function that create a node that holds what inside the t_cont
void	ft_link_all_in_containers(t_token *token, t_cont **container)
{
	t_token		*head;
	t_tmp_cont	*tmp;
	int			i;
	int			j;
	int			z;
	int			y;

	(1) && (head = token, i = 0, j = 0, z = 0, y = 0);
	tmp = NULL;
	while (head != NULL)
	{
		(1) && (i = 0, j = 0, z = 0, y = 0);
		while(head != NULL && head->type != PIPE)
		{
			if (head->type == CMD)
				tmp->cmd = head->token;
			else if (head->type == ARG)
				tmp->arg[i++] = head->token;
			else if (head->type == INFILE)
				tmp->infile[j++] = head->next->token;
			else if (head->type == APPEND)
				tmp->append[z++] = head->next->token;
			else if (head->type == OUTFILE)
				tmp->outfile[y++] = head->next->token;
			head = head->next;
		}
		(1) && (tmp->arg[i] = 0, tmp->infile[j] = 0, tmp->outfile[z] = 0, tmp->append[y] = 0);
		ft_push_container(tmp, container);
		if (head->type == PIPE)
			head = head->next;
	}
}

// void	ft_execute_one_cmd(t_cont *container)
// {
	
// }

void	ft_execution(t_token **token)
{
	t_token			*head;
	t_cont			*container;
	unsigned int	nbr_cmd;

	head = *token;
	nbr_cmd = 0;
	while (head)
	{
		if (head->type == CMD)
			nbr_cmd++;
		head = head->next;
	}
	ft_link_all_in_containers(*token, &container);
	int i = 0;
	while (container != NULL)
	{
		printf("CMD = %s\n", container->cmd);
		while (container->arg[i] != 0)
			printf("ARG = %s\n", container->arg[i++]);
		i = 0;
		while (container->infile[i] != 0)
			printf("INFILE = %s\n", container->infile[i++]);
		i = 0;
		while (container->outfile[i] != 0)
			printf("OUTFILE = %s\n", container->outfile[i++]);
		while (container->append[i] != 0)
			printf("APPEND = %s\n", container->append[i++]);
		container = container->next;
	}
	ft_free_tokens(token);
	// if (nbr_cmd == 0)
	// 	ft_execute_one_cmd(container);
}
