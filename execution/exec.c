/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musashi <musashi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/12 16:10:30 by musashi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_allocation(void *str)
{
	if (str == NULL)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
}

void	ft_free_allocation(t_tmp_cont **tmp)
{
	int	i;

	i = 0;
	free((*tmp)->cmd);
	while ((*tmp)->arg[i] != NULL)
		(1) && (free((*tmp)->arg[i]), i++);
	free((*tmp)->arg);
	i = 0;
	while ((*tmp)->infile[i] != NULL)
		(1) && (free((*tmp)->infile[i]), i++);
	free((*tmp)->infile);
	i = 0;
	while ((*tmp)->outfile[i] != NULL)
		(1) && (free((*tmp)->outfile[i]), i++);
	free((*tmp)->outfile);
	i = 0;
	while ((*tmp)->append[i] != NULL)
		(1) && (free((*tmp)->append[i]), i++);
	free((*tmp)->append);
	free(*tmp);
}

void	ft_count_for_pointers(t_token *head, t_tmp_cont	**cont)
{
	t_token	*temp;
	t_count	count;

	temp = head;
	(1) && (count.arg = 0, count.infile = 0, count.outfile = 0, count.append = 0);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == ARG)
			count.arg++;
		else if (temp->type == INFILE)
			count.infile++;
		else if (temp->type == OUTFILE)
			count.outfile++;
		else if (temp->type == APPEND)
			count.append++;
		temp = temp->next;
	}
	(*cont) = malloc(sizeof(t_tmp_cont));
	ft_check_allocation((*cont));
	(*cont)->arg = malloc((count.arg + 1) * sizeof(char *));
	ft_check_allocation((*cont)->arg);
	(*cont)->infile = malloc((count.infile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->infile);
	(*cont)->outfile = malloc((count.outfile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->outfile);
	(*cont)->append = malloc((count.append + 1) * sizeof(char *));
	ft_check_allocation((*cont)->append);
}

//	create a function that create a node that holds what inside the t_cont
void ft_link_all_in_containers(t_token *token, t_cont **container)
{
	t_token		*head;
	t_tmp_cont	*tmp;
	int			i;
	int			j;
	int			z;
	int			y;

	(1) && (*container = NULL, head = token, i = 0, j = 0, z = 0, y = 0);
	while (head != NULL)
	{
		(1) && (i = 0, j = 0, z = 0, y = 0);
		ft_count_for_pointers(head, &tmp);
		while (head != NULL && head->type != PIPE)
		{
			if (head->type == CMD)
				tmp->cmd = ft_strdup(head->token);
			else if (head->type == ARG)
				tmp->arg[i++] = ft_strdup(head->token);
			else if (head->type == INFILE)
				tmp->infile[j++] = ft_strdup(head->next->token);
			else if (head->type == APPEND)
				tmp->append[z++] = ft_strdup(head->next->token);
			else if (head->type == OUTFILE)
				tmp->outfile[y++] = ft_strdup(head->next->token);
			head = head->next;
		}
		(1) && (tmp->arg[i] = 0, tmp->infile[j] = 0, tmp->append[z] = 0, tmp->outfile[y] = 0);
		ft_push_container(tmp, container);
		ft_free_allocation(&tmp);
		if (head == NULL)
			break ;
		if (head != NULL && head->type == PIPE)
			head = head->next;
	}
}

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
	ft_print_container(container);
	// if (nbr_cmd == 0)
	// 	ft_execute_one_cmd(container);
}
