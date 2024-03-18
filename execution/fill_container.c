/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:31:07 by iassil            #+#    #+#             */
/*   Updated: 2024/03/18 13:38:07 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_alc(t_token *head, t_tmp_cont	**cont)
{
	t_token	*temp;
	t_count	c;

	(1) && (temp = head, (*cont) = malloc(sizeof(t_tmp_cont)));
	ft_check_allocation((*cont));
	(1) && (c.arg = 0, c.infile = 0, c.outfile = 0);
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == ARG)
			c.arg++;
		else if (temp->type == INFILE)
			c.infile++;
		else if (temp->type == OUTFILE || temp->type == APPEND)
			c.outfile++;
		temp = temp->next;
	}
	(*cont)->arg = malloc((c.arg + 1) * sizeof(char *));
	ft_check_allocation((*cont)->arg);
	(*cont)->inf = malloc((c.infile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->inf);
	(*cont)->outf = malloc((c.outfile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->outf);
	(*cont)->out_t = malloc((c.outfile + 1) * sizeof(int));
	ft_check_allocation((*cont)->out_t);
}

//	create a function that create a node that holds what inside the t_cont
void	ft_link_all_in_containers(t_token *head, t_cont **container)
{
	t_tmp_cont	*t;
	t_cc		c;

	*container = NULL;
	while (head != NULL)
	{
		(1) && (c.i = 0, c.j = 0, c.z = 0, c.y = 0);
		ft_count_alc(head, &t);
		t->cmd = NULL;
		while (head != NULL && head->type != PIPE)
		{
			if (head->type == CMD)
				t->cmd = ft_strdup(head->token);
			else if (head->type == ARG)
				t->arg[c.i++] = ft_strdup(head->token);
			else if (head->type == INFILE)
				t->inf[c.j++] = ft_strdup(head->next->token);
			else if (head->type == OUTFILE || head->type == APPEND)
			{
				t->outf[c.y] = ft_strdup(head->next->token);
				if (head->type == OUTFILE)
					t->out_t[c.y] = 1;
				if (head->type == APPEND)
					t->out_t[c.y] = 2;
				c.y++;
			}
			head = head->next;
		}
		(1) && (t->arg[c.i] = 0, t->inf[c.j] = 0, t->outf[c.y] = 0, t->out_t[c.y] = 0);
		(ft_push_container(t, container), ft_free_tmp(&t));
		if (head != NULL && head->type == PIPE)
			head = head->next;
	}
}
