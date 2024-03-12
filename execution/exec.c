/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: musashi <musashi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:50 by iassil            #+#    #+#             */
/*   Updated: 2024/03/12 17:14:33 by musashi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_check_allocation(void *str)
{
	if (str == NULL)
		(write(2, "Error: Allocation failed\n", 25), exit(FAIL));
}

void	ft_free_tmp(t_tmp_cont **tmp)
{
	int	i;

	i = 0;
	free((*tmp)->cmd);
	while ((*tmp)->arg[i] != NULL)
		(1) && (free((*tmp)->arg[i]), i++);
	free((*tmp)->arg);
	i = 0;
	while ((*tmp)->inf[i] != NULL)
		(1) && (free((*tmp)->inf[i]), i++);
	free((*tmp)->inf);
	i = 0;
	while ((*tmp)->outf[i] != NULL)
		(1) && (free((*tmp)->outf[i]), i++);
	free((*tmp)->outf);
	i = 0;
	while ((*tmp)->ap[i] != NULL)
		(1) && (free((*tmp)->ap[i]), i++);
	free((*tmp)->ap);
	free(*tmp);
}

void	ft_count_alc(t_token *head, t_tmp_cont	**cont)
{
	t_token	*temp;
	t_count	c;

	(1) && (temp = head, (*cont) = malloc(sizeof(t_tmp_cont)));
	ft_check_allocation((*cont));
	(1) && (c.arg = 0, c.infile = 0, c.outfile = 0, c.append = 0);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == ARG)
			c.arg++;
		else if (temp->type == INFILE)
			c.infile++;
		else if (temp->type == OUTFILE)
			c.outfile++;
		else if (temp->type == APPEND)
			c.append++;
		temp = temp->next;
	}
	(*cont)->arg = malloc((c.arg + 1) * sizeof(char *));
	ft_check_allocation((*cont)->arg);
	(*cont)->inf = malloc((c.infile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->inf);
	(*cont)->outf = malloc((c.outfile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->outf);
	(*cont)->ap = malloc((c.append + 1) * sizeof(char *));
	ft_check_allocation((*cont)->ap);
}

//	create a function that create a node that holds what inside the t_cont
void ft_link_all_in_containers(t_token *head, t_cont **container)
{
	t_tmp_cont	*t;
	t_cc		c;

	(1) && (*container = NULL);
	while (head != NULL)
	{
		((1) && (c.i = 0, c.j = 0, c.z = 0, c.y = 0), ft_count_alc(head, &t));
		while (head != NULL && head->type != PIPE)
		{
			if (head->type == CMD)
				t->cmd = ft_strdup(head->token);
			else if (head->type == ARG)
				t->arg[c.i++] = ft_strdup(head->token);
			else if (head->type == INFILE)
				t->inf[c.j++] = ft_strdup(head->next->token);
			else if (head->type == APPEND)
				t->ap[c.z++] = ft_strdup(head->next->token);
			else if (head->type == OUTFILE)
				t->outf[c.y++] = ft_strdup(head->next->token);
			head = head->next;
		}
		(1) && (t->arg[c.i] = 0, t->inf[c.j] = 0, t->ap[c.z] = 0, t->outf[c.y] = 0);
		(ft_push_container(t, container), ft_free_tmp(&t));
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
