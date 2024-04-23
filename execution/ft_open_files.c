/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:56:58 by iassil            #+#    #+#             */
/*   Updated: 2024/04/23 20:33:49 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_ambigous_and_wildcard(char *filename, int is_amb)
{
	char	**dir;
	int		i;

	i = 0;
	dir = NULL;
	if (is_amb == 1)
		return (1);
	if (ft_strchr(filename, '*'))
	{
		dir = ft_wildcards(&filename);
		while (dir && dir[i])
			i++;
		ft_f(dir);
		if (i >= 2)
			return (1);
	}
	return (0);
}

static int	ft_open_outfiles(t_info *info, t_cont *cont, int o, t_struct *s)
{
	t_fd_	fd;

	if (ft_check_ambigous_and_wildcard(cont->outfile[o], cont->out_is_amb[o]))
		return (s->status = 1, 1);
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

	if (ft_check_ambigous_and_wildcard(cont->infile[i], cont->inf_is_amb[i]))
		return (s->status = 1, 1);
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
