/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_index_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 20:10:13 by iassil            #+#    #+#             */
/*   Updated: 2024/04/24 11:07:04 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_allocate_for_index_cont(t_cont **cont)
{
	int	i;

	i = 0;
	while ((*cont)->infile && (*cont)->infile[i])
		i++;
	(*cont)->infile_index = malloc((i + 1) * sizeof(int));
	ft_check_allocation((*cont)->infile_index);
	(*cont)->inf_is_amb = malloc((i + 1) * sizeof(int));
	ft_check_allocation((*cont)->inf_is_amb);
	(*cont)->nbr_files = i;
	i = 0;
	while ((*cont)->outfile && (*cont)->outfile[i])
		i++;
	(*cont)->outfile_index = malloc((i + 1) * sizeof(int));
	ft_check_allocation((*cont)->outfile_index);
	(*cont)->out_is_amb = malloc((i + 1) * sizeof(int));
	ft_check_allocation((*cont)->out_is_amb);
	(*cont)->nbr_files += i;
}

void	ft_index_outfiles(int *i, t_token *tok, t_cont *cont, t_file *h)
{
	cont->outfile_index[*i] = tok->next->findex;
	if (cont->outfile_is_var[*i] == 1)
	{
		cont->out_is_amb[*i] = h->status;
		cont->out_before[*i] = ft_strdup(h->before);
		h = h->next;
	}
	else
	{
		cont->out_is_amb[*i] = 0;
		cont->out_before[*i] = ft_strdup("\0");
	}
	(*i)++;
}

void	ft_index_infiles(int *j, t_token *tok, t_cont *cont, t_file *h)
{
	cont->infile_index[*j] = tok->next->findex;
	if (cont->infile_is_var[*j] == 1)
	{
		cont->inf_is_amb[*j] = h->status;
		cont->inf_before[*j] = ft_strdup(h->before);
		h = h->next;
	}
	else
	{
		cont->inf_is_amb[*j] = 0;
		cont->inf_before[*j] = ft_strdup("\0");
	}
	(*j)++;
}

void	ft_index_files(t_token *head, t_cont **container, t_struct *s)
{
	t_index_files	i;

	(1) && (i.cont = *container, i.tok = head);
	(1) && (i.index_len = 0, i.h = s->head);
	while (i.cont != NULL)
	{
		ft_allocate_for_index_cont(&i.cont);
		(1) && (i.i = 0, i.j = 0);
		while (i.tok != NULL && i.tok->type != PIPE)
		{
			if (i.tok->type == APPEND || i.tok->type == OUTFILE)
				ft_index_outfiles(&i.i, i.tok, i.cont, i.h);
			else if (i.tok->type == INFILE)
				ft_index_infiles(&i.j, i.tok, i.cont, i.h);
			i.tok = i.tok->next;
		}
		(1) && (i.cont->outfile_index[i.i] = 0, i.cont->infile_index[i.j] = 0);
		(1) && (i.cont->out_before[i.i] = 0, i.cont->inf_before[i.j] = 0);
		if (i.tok && i.tok->type == PIPE)
			i.tok = i.tok->next;
		i.cont = i.cont->next;
	}
}
