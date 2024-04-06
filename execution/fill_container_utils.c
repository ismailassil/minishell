/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_container_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 03:09:08 by iassil            #+#    #+#             */
/*   Updated: 2024/04/06 03:09:56 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_allocate_for_arg_types(t_tmp_cont	**cont, t_count c)
{
	(*cont)->inf_is_var = malloc((c.infile + 1) * sizeof(int));
	ft_check_allocation((*cont)->inf_is_var);
	(*cont)->inf_is_quote = malloc((c.infile + 1) * sizeof(int));
	ft_check_allocation((*cont)->inf_is_quote);
	(*cont)->out_is_var = malloc((c.outfile + 1) * sizeof(int));
	ft_check_allocation((*cont)->out_is_var);
	(*cont)->out_is_quote = malloc((c.outfile + 1) * sizeof(int));
	ft_check_allocation((*cont)->out_is_quote);
	(*cont)->arg_is_var = malloc((c.arg + 1) * sizeof(int));
	ft_check_allocation((*cont)->arg_is_var);
	(*cont)->arg_is_quote = malloc((c.arg + 1) * sizeof(int));
	ft_check_allocation((*cont)->arg_is_quote);
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
	ft_allocate_for_arg_types(cont, c);
}

void	ft_fill_outfile_append(t_token *head, t_tmp_cont *t, t_cc *c)
{
	if (head->type == OUTFILE || head->type == APPEND)
	{
		t->outf[c->y] = ft_strdup(head->next->token);
		ft_check_allocation(t->outf[c->y]);
		if (head->type == OUTFILE)
			t->out_t[c->y] = 1;
		if (head->type == APPEND)
			t->out_t[c->y] = 2;
		(1) && (t->out_is_var[c->y] = 2, t->out_is_quote[c->y] = 2);
		if (head->next->is_var == 1)
			t->out_is_var[c->y] = 1;
		if (head->next->is_quote == 1)
			t->out_is_quote[c->y] = 1;
		c->y++;
	}
}

void	ft_fill_infile_outfile_here_doc(t_token *head, t_tmp_cont *t, t_cc *c)
{
	if (head->type == INFILE)
	{
		t->inf[c->j] = ft_strdup(head->next->token);
		ft_check_allocation(t->inf[c->j]);
		(1) && (t->inf_is_var[c->j] = 2, t->inf_is_quote[c->j] = 2);
		if (head->next->is_var == 1)
			t->inf_is_var[c->j] = 1;
		if (head->next->is_quote == 1)
			t->inf_is_quote[c->j] = 1;
		(1) && (*t->file_or_heredoc = 0, c->j++);
	}
	else if (head->type == HEREDOC)
	{
		t->here_doc[c->h] = ft_strdup(head->next->token);
		ft_check_allocation(t->here_doc[c->h++]);
		*t->file_or_heredoc = 1;
	}
	else
		ft_fill_outfile_append(head, t, c);
}
