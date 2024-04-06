/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:31:07 by iassil            #+#    #+#             */
/*   Updated: 2024/04/06 03:10:03 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_(t_token *head, t_count *c)
{
	t_token	*temp;

	temp = head;
	while (temp != NULL && temp->type != PIPE)
	{
		if (temp->type == ARG)
			c->arg++;
		else if (temp->type == INFILE)
			c->infile++;
		else if (temp->type == OUTFILE || temp->type == APPEND)
			c->outfile++;
		else if (temp->type == HEREDOC)
			c->here_doc++;
		temp = temp->next;
	}
}

void	ft_fill_container(t_token *head, t_tmp_cont *t, t_cc *c)
{
	if (head->type == CMD)
	{
		t->cmd = ft_strdup(head->token);
		ft_check_allocation(t->cmd);
		(1) && (t->cmd_is_var = 2, t->cmd_is_quote = 2);
		if (head->is_var == 1)
			t->cmd_is_var = 1;
		if (head->is_quote == 1)
			t->cmd_is_quote = 1;
	}
	else if (head->type == ARG)
	{
		t->arg[c->i] = ft_strdup(head->token);
		ft_check_allocation(t->arg[c->i]);
		(1) && (t->arg_is_var[c->i] = 2, t->arg_is_quote[c->i] = 2);
		if (head->is_var == 1)
			t->arg_is_var[c->i] = 1;
		if (head->is_quote == 1)
			t->arg_is_quote[c->i] = 1;
		c->i++;
	}
	else
		ft_fill_infile_outfile_here_doc(head, t, c);
}

void	ft_link_all_in_containers(t_token *head, t_cont **container)
{
	t_tmp_cont	*t;
	t_cc		c;

	*container = NULL;
	while (head != NULL)
	{
		(1) && (c.i = 0, c.j = 0, c.z = 0, c.y = 0, c.h = 0);
		ft_allocate_tmp_cont(head, &t);
		t->cmd = NULL;
		while (head != NULL && head->type != PIPE)
		{
			ft_fill_container(head, t, &c);
			head = head->next;
		}
		(1) && (t->arg[c.i] = 0, t->inf[c.j] = 0, \
			t->outf[c.y] = 0, t->out_t[c.y] = 0, \
			t->out_is_var[c.y] = 0, t->inf_is_var[c.j] = 0, \
			t->here_doc[c.h] = 0);
		(ft_push_container(t, container), ft_free_tmp(&t));
		if (head != NULL && head->type == PIPE)
			head = head->next;
	}
}
