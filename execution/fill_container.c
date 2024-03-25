/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_container.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:31:07 by iassil            #+#    #+#             */
/*   Updated: 2024/03/23 18:04:10 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_count_(t_token *head, t_count	*c)
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

void	ft_allocate_tmp_cont(t_token *head, t_tmp_cont	**cont)
{
	t_count	c;

	(*cont) = malloc(sizeof(t_tmp_cont));
	ft_check_allocation((*cont));
	(1) && (c.arg = 0, c.infile = 0, c.outfile = 0, c.here_doc = 0);
	ft_count_(head, &c);
	(*cont)->arg = malloc((c.arg + 1) * sizeof(char *));
	ft_check_allocation((*cont)->arg);
	(*cont)->inf = malloc((c.infile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->inf);
	(*cont)->outf = malloc((c.outfile + 1) * sizeof(char *));
	ft_check_allocation((*cont)->outf);
	(*cont)->out_t = malloc((c.outfile + 1) * sizeof(int));
	ft_check_allocation((*cont)->out_t);
	(*cont)->here_doc = malloc((c.here_doc + 1) * sizeof(char *));
	ft_check_allocation((*cont)->here_doc);
	(*cont)->file_or_heredoc = malloc(sizeof(int));
	ft_check_allocation((*cont)->file_or_heredoc);
}

void	ft_fill_rest(t_token *head, t_tmp_cont *t, t_cc *c)
{
	if (head->type == OUTFILE || head->type == APPEND)
	{
		t->outf[c->y] = ft_strdup(head->next->token);
		ft_check_allocation(t->outf[c->y]);
		if (head->type == OUTFILE)
			t->out_t[c->y] = 1;
		if (head->type == APPEND)
			t->out_t[c->y] = 2;
		c->y++;
	}
	else if (head->type == HEREDOC)
	{
		t->here_doc[c->h] = ft_strdup(head->next->token);
		ft_check_allocation(t->here_doc[c->h++]);
		*t->file_or_heredoc = 1;
	}
}

void	ft_fill_container(t_token *head, t_tmp_cont *t, t_cc *c)
{
	if (head->type == CMD)
	{
		t->cmd = ft_strdup(head->token);
		ft_check_allocation(t->cmd);
	}
	else if (head->type == ARG)
	{
		t->arg[c->i] = ft_strdup(head->token);
		ft_check_allocation(t->arg[c->i++]);
	}
	else if (head->type == INFILE)
	{
		t->inf[c->j] = ft_strdup(head->next->token);
		ft_check_allocation(t->inf[c->j++]);
		*t->file_or_heredoc = 0;
	}
	else
		ft_fill_rest(head, t, c);
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
			t->here_doc[c.h] = 0);
		(ft_push_container(t, container), ft_free_tmp(&t));
		if (head != NULL && head->type == PIPE)
			head = head->next;
	}
}
