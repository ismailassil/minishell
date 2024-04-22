/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:56:58 by iassil            #+#    #+#             */
/*   Updated: 2024/04/22 13:45:29 by iassil           ###   ########.fr       */
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
	(*cont)->nbr_files = i;
	i = 0;
	while ((*cont)->outfile && (*cont)->outfile[i])
		i++;
	(*cont)->outfile_index = malloc((i + 1) * sizeof(int));
	ft_check_allocation((*cont)->outfile_index);
	(*cont)->nbr_files += i;
}

void	ft_index_files(t_token *head, t_cont **container)
{
	t_index_files	i;

	(1) && (i.cont = *container, i.tok = head, i.index_len = 0);
	while (i.cont != NULL)
	{
		ft_allocate_for_index_cont(&i.cont);
		(1) && (i.i = 0, i.j = 0);
		while (i.tok != NULL && i.tok->type != PIPE)
		{
			if (i.tok->type == APPEND || i.tok->type == OUTFILE)
				i.cont->outfile_index[i.i++] = i.tok->next->findex;
			else if (i.tok->type == INFILE)
				i.cont->infile_index[i.j++] = i.tok->next->findex;
			i.tok = i.tok->next;
		}
		(1) && (i.cont->outfile_index[i.i] = 0, i.cont->infile_index[i.j] = 0);
		if (i.tok && i.tok->type == PIPE)
			i.tok = i.tok->next;
		i.cont = i.cont->next;
	}
}

static int	ft_open_outfiles(t_info *info, t_cont *cont, int o, t_struct *s)
{
	t_fd_	fd;

	// Check ambigious
	if (cont->outfile_type[o] == 1)
		fd.outfile = open(cont->outfile[o], CR | WO, 0644);
	else if (cont->outfile_type[o] == 2)
		fd.outfile = open(cont->outfile[o], CR | WO | AP, 0644);
	if (fd.outfile == -1)
		return (ft_throw_error(cont->outfile[o]), s->status = 1, 1);
	if (cont->outfile && cont->outfile[o + 1] != 0)
		ft_syscall(close(fd.outfile), "close");
	else
	{
		info->fd.outfile = fd.outfile;
		info->fd.opened_fd[info->fd.len++] = info->fd.outfile;
	}
	return (0);
}

static int	ft_open_infiles(t_info *info, t_cont *cont, int i, t_struct *s)
{
	t_fd_	fd;

	// Check ambigious
	fd.infile = open(cont->infile[i], O_RDONLY);
	if (fd.infile == -1)
		return (ft_throw_error(cont->infile[i]), s->status = 1, 1);
	if (cont->infile && cont->infile[i + 1] != 0)
		ft_syscall(close(fd.infile), "close");
	else
	{
		info->fd.infile = fd.infile;
		info->fd.opened_fd[info->fd.len++] = info->fd.infile;
	}
	return (0);
}

int	ft_open_files(t_cont *c, t_info *info, t_struct *s)
{
	t_open_files	f;

	f.cont = c;
	(1) && (f.i = 0, f.o = 0, f.index = 0, f.nbr_files = f.cont->nbr_files);
	while (f.nbr_files > 0)
	{
		if (c->outfile && f.cont->outfile[f.o] != 0
			&& f.cont->outfile_index[f.o] == f.index)
		{
			if (ft_open_outfiles(info, f.cont, f.o, s))
				return (1);
			f.o++;
		}
		else if (c->infile && f.cont->infile[f.i] != 0
			&& f.cont->infile_index[f.i] == f.index)
		{
			if (ft_open_infiles(info, f.cont, f.i, s))
				return (1);
			f.i++;
		}
		(1) && (f.index++, f.nbr_files--);
	}
	if (*f.cont->file_or_heredoc == 1)
		info->fd.infile = *f.cont->here_doc_fd;
	return (0);
}
