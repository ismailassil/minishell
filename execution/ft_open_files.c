/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iassil <iassil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:56:58 by iassil            #+#    #+#             */
/*   Updated: 2024/04/26 15:46:20 by iassil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_wildcard(char **filename)
{
	t_amb_rdt	r;

	r.i = 0;
	r.dir = NULL;
	r.dir = ft_wildcards(filename);
	while (r.dir && r.dir[r.i])
		r.i++;
	if (r.i >= 2)
		return (ft_error("msh: "), ft_error(*filename), \
			ft_f(r.dir), ft_error(AMB), 1);
	if (r.dir == NULL || r.dir[0] == 0)
	{
		if (ft_strchr(*filename, '"') || ft_strchr(*filename, '\''))
		{
			r.tmp = ft_strdup(*filename);
			free(*filename);
			*filename = ft_trim_quotes(r.tmp);
			free(r.tmp);
		}
		return (ft_f(r.dir), 0);
	}
	free(*filename);
	*filename = ft_strdup(r.dir[0]);
	ft_f(r.dir);
	return (0);
}

static int	ft_check_ambigous_and_wildcard(char **filename, \
	int is_amb, int is_var, char *before)
{
	char	**ptr;
	int		i;

	ptr = NULL;
	i = 0;
	if (is_var == 1 && is_amb == 1)
		return (ft_error("msh: "), ft_error(before), ft_error(AMB), 1);
	if (ft_strchr(*filename, '*'))
	{
		if (ft_check_wildcard(filename))
			return (1);
	}
	if (is_var == 1 && ft_iswhitespace(*filename))
	{
		ptr = ft_split_vquote(*filename);
		ft_check_allocation(ptr);
		free(*filename);
		*filename = ptr[0];
	}
	return (0);
}

static int	ft_open_outfiles(t_info *info, t_cont *cont, int o, t_struct *s)
{
	t_fd_	fd;

	if (ft_check_ambigous_and_wildcard(&cont->outfile[o], \
		cont->out_is_amb[o], cont->outfile_is_var[o], cont->out_before[o]))
		return (s->status = 1, 1);
	ft_check_special_quote(&cont->outfile[o]);
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

	if (ft_check_ambigous_and_wildcard(&cont->infile[i], \
		cont->inf_is_amb[i], cont->infile_is_var[i], cont->inf_before[i]))
		return (s->status = 1, 1);
	ft_check_special_quote(&cont->infile[i]);
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
